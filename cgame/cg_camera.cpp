//Client camera controls for cinematics

#include "cg_local.h"
#include "..\game\g_roff.h"

bool		in_camera = false;
camera_t	client_camera={0};
extern qboolean	player_locked;

extern gentity_t *G_Find (gentity_t *from, int fieldofs, char *match);
extern void G_SetOrigin( gentity_t *ent, vec3_t origin );
extern void G_UseTargets (gentity_t *ent, gentity_t *activator);
void CGCam_FollowDisable( void );
void CGCam_TrackDisable( void );
void CGCam_Distance( float distance, qboolean initLerp );
void CGCam_DistanceDisable( void );
extern int CG_CalcFOVFromX( float fov_x );

/*
TODO:
CloseUp, FullShot & Longshot commands:

  camera( CLOSEUP, <entity targetname>, angles(pitch yaw roll) )
  Will find the ent, apply angle offset to their head forward(minus pitch),
  get a preset distance away and set the FOV.  Trace to point, if less than
  1.0, put it there and open up FOV accordingly.
  Be sure to frame it so that eyespot and tag_head are positioned at proper
  places in the frame - ie: eyespot not in center, but not closer than 1/4
  screen width to the top...?
*/
/*
-------------------------
CGCam_Init
-------------------------
*/

void CGCam_Init( void )
{
	extern qboolean qbVidRestartOccured;
	if (!qbVidRestartOccured)
	{
		memset( &client_camera, 0, sizeof ( camera_t ) );
	}
}

/*
-------------------------
CGCam_Enable
-------------------------
*/
extern void CG_CalcVrect(void);
void CGCam_Enable( void )
{
	if (!cg.refdef.height) {
		CG_CalcVrect();
	}
	client_camera.bar_alpha = 0.0f;
	client_camera.bar_time = cg.time;

	client_camera.bar_alpha_source = 0.0f;
	client_camera.bar_alpha_dest = 1.0f;
	
	client_camera.bar_height_source = 0.0f;
	client_camera.bar_height_dest = cg.refdef.height/10;
	client_camera.bar_height = 0.0f;

	client_camera.info_state |= CAMERA_BAR_FADING;

	client_camera.FOV	= CAMERA_DEFAULT_FOV;
	client_camera.FOV2	= CAMERA_DEFAULT_FOV;

	in_camera = true;

	client_camera.next_roff_time = 0;

	if ( &g_entities[0] && g_entities[0].client )
	{
		//Player zero not allowed to do anything
		VectorClear( g_entities[0].client->ps.velocity );
		g_entities[0].contents = 0;
	}
}
/*
-------------------------
CGCam_Disable
-------------------------
*/

void CGCam_Disable( void )
{
	in_camera = false;

	client_camera.bar_alpha = 1.0f;
	client_camera.bar_time = cg.time;

	client_camera.bar_alpha_source = 1.0f;
	client_camera.bar_alpha_dest = 0.0f;
	
	client_camera.bar_height_source = cg.refdef.height/10;
	client_camera.bar_height_dest = 0.0f;

	client_camera.info_state |= CAMERA_BAR_FADING;

	if ( &g_entities[0] && g_entities[0].client )
	{
		g_entities[0].contents = MASK_PLAYERSOLID;
	}

	gi.SendServerCommand( NULL, "cts");

}

/*
-------------------------
CGCam_SetPosition
-------------------------
*/

void CGCam_SetPosition( vec3_t org )
{
	VectorCopy( org, client_camera.origin );
	VectorCopy( client_camera.origin, cg.refdef.vieworg );
}

/*
-------------------------
CGCam_Move
-------------------------
*/

void CGCam_Move( vec3_t dest, float duration )
{
	if ( client_camera.info_state & CAMERA_ROFFING )
	{
		client_camera.info_state &= ~CAMERA_ROFFING;
	}

	CGCam_TrackDisable();
	CGCam_DistanceDisable();

	if ( !duration )
	{
		client_camera.info_state &= ~CAMERA_MOVING;
		CGCam_SetPosition( dest );
		return;
	}

	client_camera.info_state |= CAMERA_MOVING;

	VectorCopy( dest, client_camera.origin2 );
	
	client_camera.move_duration = duration;
	client_camera.move_time = cg.time;
}

/*
-------------------------
CGCam_SetAngles
-------------------------
*/

void CGCam_SetAngles( vec3_t ang )
{
	VectorCopy( ang, client_camera.angles );
	VectorCopy(client_camera.angles, cg.refdefViewAngles );
}

/*
-------------------------
CGCam_Pan
-------------------------
*/

void CGCam_Pan( vec3_t dest, vec3_t panDirection, float duration )
{
	//vec3_t	panDirection = {0, 0, 0};
	int		i;
	float	delta1 , delta2;

	CGCam_FollowDisable();
	CGCam_DistanceDisable();

	if ( !duration )
	{
		CGCam_SetAngles( dest );
		client_camera.info_state &= ~CAMERA_PANNING;
		return;
	}

	//FIXME: make the dest an absolute value, and pass in a
	//panDirection as well.  If a panDirection's axis value is
	//zero, find the shortest difference for that axis.
	//Store the delta in client_camera.angles2. 
	for( i = 0; i < 3; i++ )
	{
		dest[i] = AngleNormalize360( dest[i] );
		delta1 = dest[i] - AngleNormalize360( client_camera.angles[i] );
		if ( delta1 < 0 )
		{
			delta2 = delta1 + 360;
		}
		else
		{
			delta2 = delta1 - 360;
		}
		if ( !panDirection[i] )
		{//Didn't specify a direction, pick shortest
			if( fabs(delta1) < fabs(delta2) )
			{
				client_camera.angles2[i] = delta1;
			}
			else
			{
				client_camera.angles2[i] = delta2;
			}
		}
		else if ( panDirection[i] < 0 )
		{
			if( delta1 < 0 )
			{
				client_camera.angles2[i] = delta1;
			}
			else if( delta1 > 0 )
			{
				client_camera.angles2[i] = delta2;
			}
			else
			{//exact
				client_camera.angles2[i] = 0;
			}
		}
		else if ( panDirection[i] > 0 )
		{
			if( delta1 > 0 )
			{
				client_camera.angles2[i] = delta1;
			}
			else if( delta1 < 0 )
			{
				client_camera.angles2[i] = delta2;
			}
			else
			{//exact
				client_camera.angles2[i] = 0;
			}
		}
	}
	//VectorCopy( dest, client_camera.angles2 );

	client_camera.info_state |= CAMERA_PANNING;
	
	client_camera.pan_duration = duration;
	client_camera.pan_time = cg.time;
}

/*
-------------------------
CGCam_SetRoll
-------------------------
*/

void CGCam_SetRoll( float roll )
{
	client_camera.angles[2] = roll;
}

/*
-------------------------
CGCam_Roll
-------------------------
*/

void CGCam_Roll( float	dest, float duration )
{
	if ( !duration )
	{
		CGCam_SetRoll( dest );
		return;
	}

	//FIXME/NOTE: this will override current panning!!!
	client_camera.info_state |= CAMERA_PANNING;
	
	VectorCopy( client_camera.angles, client_camera.angles2 );
	client_camera.angles2[2] = AngleDelta( dest, client_camera.angles[2] );
	
	client_camera.pan_duration = duration;
	client_camera.pan_time = cg.time;
}

/*
-------------------------
CGCam_SetFOV
-------------------------
*/

void CGCam_SetFOV( float FOV )
{
	client_camera.FOV = FOV;
}

/*
-------------------------
CGCam_Zoom
-------------------------
*/

void CGCam_Zoom( float FOV, float duration )
{
	if ( !duration )
	{
		CGCam_SetFOV( FOV );
		return;
	}
	client_camera.info_state |= CAMERA_ZOOMING;

	client_camera.FOV_time	= cg.time;
	client_camera.FOV2		= FOV;

	client_camera.FOV_duration = duration;
}

/*
-------------------------
CGCam_Fade
-------------------------
*/

void CGCam_SetFade( vec4_t dest )
{//Instant completion
	client_camera.info_state &= ~CAMERA_FADING;
	client_camera.fade_duration = 0;
	Vector4Copy( dest, client_camera.fade_source );
	Vector4Copy( dest, client_camera.fade_color );
}

/*
-------------------------
CGCam_Fade
-------------------------
*/

void CGCam_Fade( vec4_t source, vec4_t dest, float duration )
{
	if ( !duration )
	{
		CGCam_SetFade( dest );
		return;
	}

	Vector4Copy( source, client_camera.fade_source );
	Vector4Copy( dest, client_camera.fade_dest );

	client_camera.fade_duration = duration;
	client_camera.fade_time = cg.time;

	client_camera.info_state |= CAMERA_FADING;
}

void CGCam_FollowDisable( void )
{
	client_camera.info_state &= ~CAMERA_FOLLOWING;
	client_camera.cameraGroup[0] = 0;
}

void CGCam_TrackDisable( void )
{
	client_camera.info_state &= ~CAMERA_TRACKING;
	client_camera.trackEntNum = ENTITYNUM_WORLD;
}

void CGCam_DistanceDisable( void )
{
	client_camera.distance = 0;
}
/*
-------------------------
CGCam_Follow
-------------------------
*/

void CGCam_Follow( const char *cameraGroup, float speed, float initLerp )
{
	int len;

	//Clear any previous
	CGCam_FollowDisable();

	if(!cameraGroup || !cameraGroup[0])
	{
		return;
	}

	if ( Q_stricmp("none", (char *)cameraGroup) == 0 )
	{//Turn off all aiming
		return;
	}
	
	//NOTE: if this interrupts a pan before it's done, need to copy the cg.refdef.viewAngles to the camera.angles!
	client_camera.info_state |= CAMERA_FOLLOWING;
	client_camera.info_state &= ~CAMERA_PANNING;

	len = strlen(cameraGroup);
	strncpy( client_camera.cameraGroup, cameraGroup, sizeof(client_camera.cameraGroup) );
	//NULL terminate last char in case they type a name too long
	client_camera.cameraGroup[len] = 0;

	if ( speed )
	{
		client_camera.followSpeed = speed;
	}
	else
	{
		client_camera.followSpeed = 100.0f;
	}

	if ( initLerp )
	{
		client_camera.followInitLerp = qtrue;
	}
	else
	{
		client_camera.followInitLerp = qfalse;
	}
}

/*
-------------------------
Q3_CameraAutoAim

  Keeps camera pointed at an entity, usually will be a misc_camera_focus
  misc_camera_focus can be on a track that stays closest to it's subjects on that
  path (like Q3_CameraAutoTrack) or is can simply always put itself between it's subjects.
  misc_camera_focus can also set FOV/camera dist needed to keep the subjects in frame
-------------------------
*/

void CG_CameraAutoAim( const char *name )
{
	/*
	gentity_t *aimEnt = NULL;

	//Clear any previous
	CGCam_FollowDisable();

	if(Q_stricmp("none", (char *)name) == 0)
	{//Turn off all aiming
		return;
	}

	aimEnt = G_Find(NULL, FOFS(targetname), (char *)name);

	if(!aimEnt)
	{
		gi.Printf(S_COLOR_RED"ERROR: %s camera aim target not found\n", name);
		return;
	}

	//Lerp time...
	//aimEnt->aimDebounceTime = level.time;//FIXME: over time
	client_camera.aimEntNum = aimEnt->s.number;
	CGCam_Follow( aimEnt->cameraGroup, aimEnt->speed, aimEnt->spawnflags&1 );
	*/
}

/*
-------------------------
CGCam_Track
-------------------------
*/
//void CGCam_Track( char *trackName, float speed, float duration )
void CGCam_Track( const char *trackName, float speed, float initLerp )
{
	gentity_t	*trackEnt = NULL;

	CGCam_TrackDisable();

	if(Q_stricmp("none", (char *)trackName) == 0)
	{//turn off tracking
		return;
	}

	//NOTE: if this interrupts a move before it's done, need to copy the cg.refdef.vieworg to the camera.origin!
	//This will find a path_corner now, not a misc_camera_track
	trackEnt = G_Find(NULL, FOFS(targetname), (char *)trackName);

	if ( !trackEnt )
	{
		gi.Printf(S_COLOR_RED"ERROR: %s camera track target not found\n", trackName);
		return;
	}

	client_camera.info_state |= CAMERA_TRACKING;
	client_camera.info_state &= ~CAMERA_MOVING;

	client_camera.trackEntNum = trackEnt->s.number;
	client_camera.initSpeed = speed/10.0f;
	client_camera.speed = speed;
	client_camera.nextTrackEntUpdateTime = cg.time;

	if ( initLerp )
	{
		client_camera.trackInitLerp = qtrue;
	}
	else
	{
		client_camera.trackInitLerp = qfalse;
	}
	/*
	if ( client_camera.info_state & CAMERA_FOLLOWING )
	{//Used to snap angles?  Do what...?
	}
	*/

	//Set a moveDir
	VectorSubtract( trackEnt->currentOrigin, client_camera.origin, client_camera.moveDir );

	if ( !client_camera.trackInitLerp )
	{//want to snap to first position
		//Snap to trackEnt's origin
		VectorCopy( trackEnt->currentOrigin, client_camera.origin );

		//Set new moveDir if trackEnt has a next path_corner
		//Possible that track has no next point, in which case we won't be moving anyway
		if ( trackEnt->target && trackEnt->target[0] )
		{
			gentity_t *newTrackEnt = G_Find( NULL, FOFS(targetname), trackEnt->target );
			if ( newTrackEnt )
			{
				VectorSubtract( newTrackEnt->currentOrigin, client_camera.origin, client_camera.moveDir );
			}
		}
	}

	VectorNormalize( client_camera.moveDir );
}

/*
-------------------------
Q3_CameraAutoTrack

  Keeps camera a certain distance from target entity but on the specified CameraPath
  The distance can be set in a script or derived from a misc_camera_focus.
  Dist will interpolate when changed, can also set acceleration/deceleration values.
  FOV will also interpolate.

  CameraPath might be a MAX path or perhaps a series of path_corners on the map itself
-------------------------
*/

void CG_CameraAutoTrack( const char *name )
{
	/*
	gentity_t *trackEnt = NULL;

	CGCam_TrackDisable();

	if(Q_stricmp("none", (char *)name) == 0)
	{//turn off tracking
		return;
	}

	//This will find a path_corner now, not a misc_camera_track
	trackEnt = G_Find(NULL, FOFS(targetname), (char *)name);

	if(!trackEnt)
	{
		gi.Printf(S_COLOR_RED"ERROR: %s camera track target not found\n", name);
		return;
	}

	//FIXME: last arg will be passed in
	CGCam_Track( trackEnt->s.number, trackEnt->speed, qfalse );
	//FIXME: this will be a seperate call
	CGCam_Distance( trackEnt->radius, qtrue);
	*/
}

/*
-------------------------
CGCam_Distance
-------------------------
*/

void CGCam_Distance( float distance, float initLerp )
{
	client_camera.distance = distance;

	if ( initLerp )
	{
		client_camera.distanceInitLerp = qtrue;
	}
	else
	{
		client_camera.distanceInitLerp = qfalse;
	}
}

//========================================================================================


void CGCam_FollowUpdate ( void )
{
	vec3_t		center, dir, cameraAngles, vec, focus[MAX_CAMERA_GROUP_SUBJECTS];//No more than 16 subjects in a cameraGroup
	gentity_t	*from = NULL;
	centity_t	*fromCent = NULL;
	int			num_subjects = 0, i;
	
	if ( client_camera.cameraGroup && client_camera.cameraGroup[0] )
	{
		//Stay centered in my cameraGroup, if I have one
		while( NULL != (from = G_Find(from, FOFS(cameraGroup), client_camera.cameraGroup)))
		{
			/*
			if ( from->s.number == client_camera.aimEntNum )
			{//This is the misc_camera_focus, we'll be removing this ent altogether eventually
				continue;
			}
			*/

			if ( num_subjects >= MAX_CAMERA_GROUP_SUBJECTS )
			{
				gi.Printf(S_COLOR_RED"ERROR: Too many subjects in shot composition %s", client_camera.cameraGroup);
				break;
			}

			fromCent = &cg_entities[from->s.number];
			if ( !fromCent )
			{
				continue;
			}

			if ( from->s.pos.trType == TR_INTERPOLATE )
			{//use interpolated origin?
				VectorCopy(fromCent->lerpOrigin, focus[num_subjects]);
			}
			else
			{
				VectorCopy(from->currentOrigin, focus[num_subjects]);
			}
			//FIXME: make a list here of their s.numbers instead so we can do other stuff with the list below
			if ( from->client )
			{//Track to their eyes - FIXME: maybe go off a tag?
				//FIXME: 
				//Based on FOV and distance to subject from camera, pick the point that
				//keeps eyes 3/4 up from bottom of screen... what about bars?
				focus[num_subjects][2] += from->client->ps.viewheight;
			}
			num_subjects++;
		}

		if ( !num_subjects )	// Bad cameragroup 
		{
			gi.Printf(S_COLOR_RED"ERROR: Camera Focus unable to locate cameragroup: %s\n", client_camera.cameraGroup);
			return;
		}

		//Now average all points
		VectorCopy( focus[0], center );
		for( i = 1; i < num_subjects; i++ )
		{
			VectorAdd( focus[i], center, center );
		}
		VectorScale( center, 1.0f/((float)num_subjects), center );
	}
	else
	{
		return;
	}

	//Need to set a speed to keep a distance from
	//the subject- fixme: only do this if have a distance
	//set
	VectorSubtract( client_camera.subjectPos, center, vec );
	client_camera.subjectSpeed = VectorLengthSquared( vec ) * 100.0f / cg.frametime;

	VectorCopy( center, client_camera.subjectPos );

	VectorSubtract( center, cg.refdef.vieworg, dir );//can't use client_camera.origin because it's not updated until the end of the move.

	//Get desired angle
	vectoangles(dir, cameraAngles);
	
	if ( client_camera.followInitLerp )
	{//Lerping
		for( i = 0; i < 3; i++ )
		{
			cameraAngles[i] = LerpAngle( client_camera.angles[i], cameraAngles[i], cg.frametime/100.0f * client_camera.followSpeed/100.f );
		}
	}
	else
	{//Snapping, should do this first time if follow_lerp_to_start_duration is zero
		//will lerp from this point on
		client_camera.followInitLerp = qtrue;
		//So tracker doesn't move right away thinking the first angle change
		//is the subject moving... FIXME: shouldn't set this until lerp done OR snapped?
		client_camera.subjectSpeed = 0;
	}

	//Point camera to lerp angles
	VectorCopy( cameraAngles, client_camera.angles );
}

void CGCam_TrackEntUpdate ( void )
{//FIXME: only do every 100 ms
	gentity_t	*trackEnt = NULL;
	gentity_t	*newTrackEnt = NULL;
	qboolean	reached = qfalse;
	vec3_t		vec;
	float		dist;

	if ( client_camera.trackEntNum >= 0 && client_camera.trackEntNum < ENTITYNUM_WORLD )
	{//We're already heading to a path_corner
		trackEnt = &g_entities[client_camera.trackEntNum];
		VectorSubtract( trackEnt->currentOrigin, client_camera.origin, vec );
		dist = VectorLengthSquared( vec );
		if ( dist < 256 )//16 squared
		{//FIXME: who should be doing the using here?
			G_UseTargets( trackEnt, trackEnt );
			reached = qtrue;
		}
	}
	
	if ( trackEnt && reached )
	{
		
		if ( trackEnt->target && trackEnt->target[0] )
		{//Find our next path_corner
			newTrackEnt = G_Find( NULL, FOFS(targetname), trackEnt->target );
			if ( newTrackEnt )
			{
				if ( newTrackEnt->radius < 0 )
				{//Don't bother trying to maintain a radius
					client_camera.distance = 0;
					client_camera.speed = client_camera.initSpeed;
				}
				else if ( newTrackEnt->radius > 0 )
				{
					client_camera.distance = newTrackEnt->radius;
				}

				if ( newTrackEnt->speed < 0 )
				{//go back to our default speed
					client_camera.speed = client_camera.initSpeed;
				}
				else if ( newTrackEnt->speed > 0 )
				{
					client_camera.speed = newTrackEnt->speed/10.0f;
				}
			}
		}
		else
		{//stop thinking if this is the last one
			CGCam_TrackDisable();
		}
	}

	if ( newTrackEnt )
	{//Update will lerp this
		client_camera.info_state |= CAMERA_TRACKING; 
		client_camera.trackEntNum = newTrackEnt->s.number; 
		VectorCopy( newTrackEnt->currentOrigin, client_camera.trackToOrg );
	}

	client_camera.nextTrackEntUpdateTime = cg.time + 100;
}

void CGCam_TrackUpdate ( void )
{
	vec3_t		goalVec, curVec, trackPos, vec;
	float		goalDist, dist;
	qboolean	slowDown = qfalse;

	if ( client_camera.nextTrackEntUpdateTime <= cg.time )
	{
		CGCam_TrackEntUpdate();
	}

	VectorSubtract( client_camera.trackToOrg, client_camera.origin, goalVec );
	goalDist = VectorNormalize( goalVec );
	if ( goalDist > 100 )
	{
		goalDist = 100;
	}
	else if ( goalDist < 10 )
	{
		goalDist = 10;
	}

	if ( client_camera.distance && client_camera.info_state & CAMERA_FOLLOWING )
	{
		float	adjust = 0.0f, desiredSpeed = 0.0f;
		float	dot;

		if ( !client_camera.distanceInitLerp )
		{
			VectorSubtract( client_camera.origin, client_camera.subjectPos, vec );
			VectorNormalize( vec );
			//FIXME: use client_camera.moveDir here?
			VectorMA( client_camera.subjectPos, client_camera.distance, vec, client_camera.origin );
			//Snap to first time only
			client_camera.distanceInitLerp = qtrue;
			return;
		}
		else if ( client_camera.subjectSpeed > 0.05f )
		{//Don't start moving until subject moves 
			VectorSubtract( client_camera.subjectPos, client_camera.origin, vec );
			dist = VectorNormalize(vec);
			dot = DotProduct(goalVec, vec);

			if ( dist > client_camera.distance )
			{//too far away
				if ( dot > 0 )
				{//Camera is moving toward the subject
					adjust = (dist - client_camera.distance);//Speed up
				}
				else if ( dot < 0 )
				{//Camera is moving away from the subject
					adjust = (dist - client_camera.distance) * -1.0f;//Slow down
				}
			}
			else if ( dist < client_camera.distance )
			{//too close
				if(dot > 0)
				{//Camera is moving toward the subject
					adjust = (client_camera.distance - dist) * -1.0f;//Slow down
				}
				else if(dot < 0)
				{//Camera is moving away from the subject
					adjust = (client_camera.distance - dist);//Speed up
				}
			}
			
			//Speed of the focus + our error
			//desiredSpeed = aimCent->gent->speed + (adjust * cg.frametime/100.0f);//cg.frameInterpolation);
			desiredSpeed = (adjust);// * cg.frametime/100.0f);//cg.frameInterpolation);
			
			//self->moveInfo.speed = desiredSpeed;
			
			//Don't change speeds faster than 10 every 10th of a second
			float	max_allowed_accel = MAX_ACCEL_PER_FRAME * (cg.frametime/100.0f);

			if ( !client_camera.subjectSpeed )
			{//full stop
				client_camera.speed = desiredSpeed;
			}
			else if ( client_camera.speed - desiredSpeed > max_allowed_accel )
			{//new speed much slower, slow down at max accel
				client_camera.speed -= max_allowed_accel;
			}
			else if ( desiredSpeed - client_camera.speed > max_allowed_accel )
			{//new speed much faster, speed up at max accel
				client_camera.speed += max_allowed_accel;
			}
			else
			{//remember this speed
				client_camera.speed = desiredSpeed;
			}

			//Com_Printf("Speed: %4.2f (%4.2f)\n", self->moveInfo.speed, aimCent->gent->speed);
		}
	}
	else
	{
		//slowDown = qtrue;
	}
	

	//FIXME: this probably isn't right, round it out more
	VectorScale( goalVec, cg.frametime/100.0f, goalVec );
	VectorScale( client_camera.moveDir, (100.0f - cg.frametime)/100.0f, curVec );
	VectorAdd( goalVec, curVec, client_camera.moveDir );
	VectorNormalize( client_camera.moveDir );
	if(slowDown)
	{
		VectorMA( client_camera.origin, client_camera.speed * goalDist/100.0f * cg.frametime/100.0f, client_camera.moveDir, trackPos );
	}
	else
	{
		VectorMA( client_camera.origin, client_camera.speed * cg.frametime/100.0f , client_camera.moveDir, trackPos );
	}

	//FIXME: Implement
	//Need to find point on camera's path that is closest to the desired distance from subject
	//OR: Need to intelligently pick this desired distance based on framing...
	VectorCopy( trackPos, client_camera.origin );
}

//=========================================================================================

/*
-------------------------
CGCam_UpdateBarFade
-------------------------
*/

void CGCam_UpdateBarFade( void )
{
	if ( client_camera.bar_time + BAR_DURATION < cg.time )
	{
		client_camera.bar_alpha = client_camera.bar_alpha_dest;
		client_camera.info_state &= ~CAMERA_BAR_FADING;
		client_camera.bar_height = client_camera.bar_height_dest;
	}
	else
	{
		client_camera.bar_alpha  = client_camera.bar_alpha_source + ( ( client_camera.bar_alpha_dest - client_camera.bar_alpha_source ) / BAR_DURATION ) * ( cg.time - client_camera.bar_time );;
		client_camera.bar_height = client_camera.bar_height_source + ( ( client_camera.bar_height_dest - client_camera.bar_height_source ) / BAR_DURATION ) * ( cg.time - client_camera.bar_time );;
	}
}

/*
-------------------------
CGCam_UpdateFade
-------------------------
*/

void CGCam_UpdateFade( void )
{
	if ( client_camera.info_state & CAMERA_FADING )
	{
		if ( client_camera.fade_time + client_camera.fade_duration < cg.time )
		{
			Vector4Copy( client_camera.fade_dest, client_camera.fade_color );
			client_camera.info_state &= ~CAMERA_FADING;
		}
		else
		{
			for ( int i = 0; i < 4; i++ )
			{
				client_camera.fade_color[i] = client_camera.fade_source[i] + (( ( client_camera.fade_dest[i] - client_camera.fade_source[i] ) ) / client_camera.fade_duration ) * ( cg.time - client_camera.fade_time );
			}
		}
	}
}
/*
-------------------------
CGCam_Update
-------------------------
*/

void CGCam_Update( void )
{
	int	i;
	qboolean	checkFollow = qfalse;
	qboolean	checkTrack = qfalse;

	// Apply new roff data to the camera as needed
	if ( client_camera.info_state & CAMERA_ROFFING )
	{
		CGCam_Roff();
	}

	//Check for a zoom
	if ( client_camera.info_state & CAMERA_ZOOMING )
	{
		float	actualFOV_X;

		if ( client_camera.FOV_time + client_camera.FOV_duration < cg.time )
		{
			actualFOV_X = client_camera.FOV = client_camera.FOV2;
			client_camera.info_state &= ~CAMERA_ZOOMING;
		}
		else
		{
			actualFOV_X = client_camera.FOV + (( ( client_camera.FOV2 - client_camera.FOV ) ) / client_camera.FOV_duration ) * ( cg.time - client_camera.FOV_time );
		}
		CG_CalcFOVFromX( actualFOV_X );
	}
	else
	{
		CG_CalcFOVFromX( client_camera.FOV );
	}

	//Check for pan
	if ( client_camera.info_state & CAMERA_PANNING )
	{
		//Note: does not actually change the camera's angles until the pan time is done!
		if ( client_camera.pan_time + client_camera.pan_duration < cg.time )
		{//finished panning
			for ( i = 0; i < 3; i++ )
			{
				client_camera.angles[i] = AngleNormalize360( ( client_camera.angles[i] + client_camera.angles2[i] ) );
			}

			client_camera.info_state &= ~CAMERA_PANNING;
			VectorCopy(client_camera.angles, cg.refdefViewAngles );
		}
		else
		{//still panning
			for ( i = 0; i < 3; i++ )
			{
				//NOTE: does not store the resultant angle in client_camera.angles until pan is done
				cg.refdefViewAngles[i] = client_camera.angles[i] + ( client_camera.angles2[i] / client_camera.pan_duration ) * ( cg.time - client_camera.pan_time );
			}
		}
	}
	else 
	{
		checkFollow = qtrue;
	}

	AnglesToAxis( cg.refdefViewAngles, cg.refdef.viewaxis );

	//Check for movement
	if ( client_camera.info_state & CAMERA_MOVING )
	{
		//NOTE: does not actually move the camera until the movement time is done!
		if ( client_camera.move_time + client_camera.move_duration < cg.time )
		{
			VectorCopy( client_camera.origin2, client_camera.origin );
			client_camera.info_state &= ~CAMERA_MOVING;
			VectorCopy( client_camera.origin, cg.refdef.vieworg );
		}
		else
		{
			for ( i = 0; i < 3; i++ )
				cg.refdef.vieworg[i] = client_camera.origin[i] + (( ( client_camera.origin2[i] - client_camera.origin[i] ) ) / client_camera.move_duration ) * ( cg.time - client_camera.move_time );
		}
	}
	else
	{
		checkTrack = qtrue;
	}

	if ( checkFollow )
	{
		if ( client_camera.info_state & CAMERA_FOLLOWING )
		{//This needs to be done after camera movement
			CGCam_FollowUpdate();
		}
		VectorCopy(client_camera.angles, cg.refdefViewAngles );
	}

	if ( checkTrack )
	{
		if ( client_camera.info_state & CAMERA_TRACKING )
		{//This has to run AFTER Follow if the camera is following a cameraGroup
			CGCam_TrackUpdate();
		}

		VectorCopy( client_camera.origin, cg.refdef.vieworg );
	}

	//Bar fading
	if ( client_camera.info_state & CAMERA_BAR_FADING )
	{
		CGCam_UpdateBarFade();
	}

	//Normal fading - separate call because can finish after camera is disabled
	CGCam_UpdateFade();

	//Update shaking if there's any
	CGCam_UpdateShake( cg.refdef.vieworg, cg.refdefViewAngles );
}

extern void CG_FillRect2( float x, float y, float width, float height, const float *color );

/*
-------------------------
CGCam_DrawFades
-------------------------
*/

void CGCam_DrawFades( void )
{
	if ( client_camera.fade_color[3] == 0.0f )
		return;

	CG_FillRect2( cg.refdef.x, cg.refdef.y, cg.refdef.width, cg.refdef.height, client_camera.fade_color );
}

/*
-------------------------
CGCam_DrawWideScreen
-------------------------
*/

void CGCam_DrawWideScreen( void )
{
	vec4_t	modulate;
	int		barHeight = client_camera.bar_height;

	//Only draw if visible
	if ( client_camera.bar_alpha )
	{
		CGCam_UpdateBarFade();

		modulate[0] = modulate[1] = modulate[2] = 0.0f;
		modulate[3] = client_camera.bar_alpha;
	
		CG_FillRect2( cg.refdef.x, cg.refdef.y, cg.refdef.width, barHeight, modulate  );
		CG_FillRect2( cg.refdef.x, cg.refdef.y+cg.refdef.height - barHeight,cg.refdef.width, barHeight, modulate  );
	}

	//NOTENOTE: Camera always draws the fades unless the alpha is 0
	CGCam_DrawFades();
}

/*
-------------------------
CGCam_RenderScene
-------------------------
*/
void CGCam_RenderScene( void )
{
	CGCam_Update();
	CG_CalcVrect();
}

/*
-------------------------
CGCam_Shake
-------------------------
*/

void CGCam_Shake( float intensity, int duration )
{
	if ( intensity > MAX_SHAKE_INTENSITY )
		intensity = MAX_SHAKE_INTENSITY;

	client_camera.shake_intensity = intensity;
	client_camera.shake_duration = duration;
	client_camera.shake_start = cg.time;
}

/*
-------------------------
CGCam_UpdateShake

This doesn't actually affect the camera's info, but passed information instead
-------------------------
*/

void CGCam_UpdateShake( vec3_t origin, vec3_t angles )
{
	vec3_t	moveDir;
	float	intensity_scale, intensity;

	if ( client_camera.shake_duration <= 0 )
		return;

	if ( cg.time > ( client_camera.shake_start + client_camera.shake_duration ) )
	{
		client_camera.shake_intensity = 0;
		client_camera.shake_duration = 0;
		client_camera.shake_start = 0;
		return;
	}

	//intensity_scale now also takes into account FOV with 90.0 as normal
	intensity_scale = 1.0f - ( (float) ( cg.time - client_camera.shake_start ) / (float) client_camera.shake_duration ) * (((client_camera.FOV+client_camera.FOV2)/2.0f)/90.0f);

	intensity = client_camera.shake_intensity * intensity_scale;

	for ( int i=0; i < 3; i++ )
		moveDir[i] = ( crandom() * intensity );

	//FIXME: Lerp

	//Move the camera
	VectorAdd( origin, moveDir, origin );

	for ( i=0; i < 3; i++ )
		moveDir[i] = ( crandom() * intensity );

	//FIXME: Lerp

	//Move the angles
	VectorAdd( angles, moveDir, angles );
}

/*
-------------------------
CGCam_StartRoff

Sets up the camera to use
a rof file
-------------------------
*/

void CGCam_StartRoff( char *roff )
{
	CGCam_FollowDisable();
	CGCam_TrackDisable();

	// Set up the roff state info..we'll hijack the moving and panning code until told otherwise 
	//	...CAMERA_FOLLOWING would be a case that could override this..
	client_camera.info_state |= CAMERA_MOVING;
	client_camera.info_state |= CAMERA_PANNING;

	if ( !G_LoadRoff( roff ) )
	{
		// The load failed so don't turn on the roff playback...
		Com_Printf( S_COLOR_RED"ROFF camera playback failed\n" );
		return;
	};

	client_camera.info_state |= CAMERA_ROFFING;

	strncpy(client_camera.sRoff,roff,sizeof(client_camera.sRoff));
	client_camera.roff_frame = 0;
	client_camera.next_roff_time = cg.time;	// I can work right away
}

/*
-------------------------
CGCam_StopRoff

Stops camera rof
-------------------------
*/

void CGCam_StopRoff( void )
{
	// Clear the roff flag
	client_camera.info_state &= ~CAMERA_ROFFING;
}

/*
------------------------------------------------------
CGCam_Roff

Applies the sampled roff data to the camera and does 
the lerping itself...this is done because the current
camera interpolation doesn't seem to work all that
great when you are adjusting the camera org and angles
so often...or maybe I'm just on crack.
------------------------------------------------------
*/

void CGCam_Roff( void )
{
	if ( cg.time < client_camera.next_roff_time )
	{
		// Nothing else to do for now...
		return; 
	}

	int roff_id;

	// Make sure that the roff is cached
	roff_id = G_LoadRoff( client_camera.sRoff );

	if ( !roff_id )
	{
		return;
	}

	roff_list_t		*roff	= &roffs[ roff_id - 1 ];
	move_rotate_t	*data	= &roff->data[ client_camera.roff_frame ];

#ifdef _DEBUG
	Com_Printf( S_COLOR_GREEN"ROFF dat: o:<%.2f %.2f %.2f> a:<%.2f %.2f %.2f>\n", 
					data->origin_delta[0], data->origin_delta[1], data->origin_delta[2],
					data->rotate_delta[0], data->rotate_delta[1], data->rotate_delta[2] );
#endif

	if ( client_camera.roff_frame )
	{
		// Don't mess with angles if we are following
		if ( !(client_camera.info_state & CAMERA_FOLLOWING) )
		{
			VectorCopy( client_camera.angles2, client_camera.angles );
		}

		VectorCopy( client_camera.origin2, client_camera.origin );
	}

	// Don't mess with angles if we are following
	if ( !(client_camera.info_state & CAMERA_FOLLOWING) )
	{
		VectorCopy( data->rotate_delta, client_camera.angles2 );
		client_camera.pan_time = cg.time;
		client_camera.pan_duration = 100;
	}

	VectorAdd( client_camera.origin, data->origin_delta, client_camera.origin2 );

	client_camera.move_time = cg.time;
	client_camera.move_duration = 100;

	if ( ++client_camera.roff_frame >= roff->frames )
	{
		CGCam_StopRoff();	
		return;
	}

	// Check back in 100 ms to get the next roff entry
	client_camera.next_roff_time = cg.time + 100;  
}

void CMD_CGCam_Disable( void )
{
	vec4_t	fade = {0, 0, 0, 0};

	CGCam_Disable();
	CGCam_SetFade( fade );
	player_locked = qfalse;
}
