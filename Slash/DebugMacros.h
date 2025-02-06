#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(location) if(GetWorld()) DrawDebugSphere(GetWorld(), location, 30.f, 12.f, FColor::Red,true);
#define DRAW_SPHERE_SINGLEFRAME(location) if(GetWorld()) DrawDebugSphere(GetWorld(), location, 30.f, 12.f, FColor::Red,false, -1.f);
#define DRAW_LINE(startLocation, endLocation) if(GetWorld()) DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, true, -1.f, 0, .5f);
#define DRAW_LINE_SINGLEFRAME(startLocation, endLocation) if(GetWorld()) DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, false, -1.f, 0, .5f);
#define DRAW_POINT(location) if(GetWorld()) DrawDebugPoint(GetWorld(), location, 30.f, FColor::Red, true);
#define DRAW_POINT_SINGLEFRAME(location) if(GetWorld()) DrawDebugPoint(GetWorld(), location, 30.f, FColor::Red, false, -1.f);
#define DRAW_VECTOR(startLocation, endLocation) if (GetWorld()) \
    {\
		DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, true, -1.f, 0, .5f);\
		DrawDebugDirectionalArrow(GetWorld(), startLocation, endLocation, 45.f, FColor::Red, true);\
	}	
#define DRAW_VECTOR_SINGLEFRAME(startLocation, endLocation) if (GetWorld()) \
    {\
		DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, false, -1.f, 0, .5f);\
		DrawDebugDirectionalArrow(GetWorld(), startLocation, endLocation, 45.f, FColor::Red, false, -1.f);\
	}	