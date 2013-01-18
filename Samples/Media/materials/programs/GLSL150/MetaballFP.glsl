#version 150

// Ogre port of Nvidia's IsoSurf.cg file
// Modified code follows. See http://developer.download.nvidia.com/SDK/10/opengl/samples.html for original
//
// Cg port of Yury Uralsky's metaball FX shader
//
// Authors: Simon Green and Yury Urlasky
// Email: sdkfeedback@nvidia.com
//
// Copyright (c) NVIDIA Corporation. All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

out vec4 fragColour;
in vec3 oNormal;

// Pixel shader
void main()
{
	//Sanitize input
	vec3 N = normalize(oNormal);
	vec3 L = vec3(0, 0, 1);
    float nDotL = dot(N, L);

	vec3 material;
	
	if(nDotL < 0.0)
    	material = vec3(0, 0, 0.5);
    else
    	material = vec3(1, 1, 1);

	fragColour = vec4(abs(nDotL) * material, 0.1);
}