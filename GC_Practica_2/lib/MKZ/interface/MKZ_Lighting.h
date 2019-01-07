#ifndef LIB_MKZ_SRC_MKZ_LIGHTING_H_
#define LIB_MKZ_SRC_MKZ_LIGHTING_H_

typedef struct {
    float r, g, b;
} MKZ_color3;

typedef struct{

	float * floatMap; //array size = n*n

	int n;

}MKZ_map;

typedef struct{

	float * floatMap1; //array size = n*n
	float * floatMap2; //array size = n*n
	float * floatMap3; //array size = n*n

	int n;

}MKZ_3map;

typedef struct{

	MKZ_3map * top;
	MKZ_3map * bottom;
	MKZ_3map * left;
	MKZ_3map * right;
	MKZ_3map * front;
	MKZ_3map * back;

}MKZ_cube_map;

typedef struct{

	MKZ_3map  * map;
	MKZ_map  * intensity_map;

}MKZ_ambient_component;

typedef MKZ_ambient_component MKZ_diffuse_component;

typedef struct{

	MKZ_3map * map;
	MKZ_map * intensity_map;
	MKZ_map * shininess_map;

}MKZ_specular_component;

typedef struct{

	MKZ_map * alpha_map;
	MKZ_map * specular_alpha_map;
	MKZ_map * fresnel_map;
	MKZ_map * blend_map;
	MKZ_map * refraction_map;

}MKZ_translucency_component;

typedef struct{

	MKZ_map * reflectivity_map;
	MKZ_3map * taint_map;
	MKZ_map * fresnel_map;
	MKZ_map * blend_map;

}MKZ_reflective_component;

typedef struct{

	//Mask containing the properties of the material (whether to use certain maps)
		unsigned int property_mask;

	//Basic Blinn-Phong ilumination

		MKZ_ambient_component * ambient;
		MKZ_diffuse_component * diffuse;
		MKZ_specular_component * specular;

	//Reflectivity and refractivity (Results depend on lighting model and whether there are Fast Approximation Cube Maps)

		MKZ_translucency_component * translucent;
		MKZ_reflective_component * reflectivity;

	//Additional geometry details

		MKZ_3map * normal_map; //Normals of the surface
		MKZ_map * displacement_map; //Displacement of the surface (similar to bump-maps, but higher precision)

	//Fast Approximation local maps, these must be precomputed (w/ Path tracing or something that produces photorealistic results)
	//Only suitable  if scene is static (lights are static and the objects in the approximation are as well)

		MKZ_map * light_map; //Local shadow map to gray-out un-lit areas
		MKZ_3map * radiance_map; //Local illumination map

		MKZ_cube_map * reflection_cube_map; // Local reflection map, will override reflection probe settings


}MKZ_material;

MKZ_color3 * MKZ_LIGHTING_create_color3();
void MKZ_LIGHTING_reset_to_black(MKZ_color3 * c3);
void MKZ_LIGHTING_free_color3(MKZ_color3 * col);

/** MATERIAL **/
MKZ_material * MKZ_LIGHTING_create_material();
MKZ_map * MKZ_LIGHTING_create_map(int size);
MKZ_3map * MKZ_LIGHTING_create_3map(int size);
MKZ_cube_map * MKZ_LIGHTING_create_cube_map();
MKZ_ambient_component * MKZ_LIGHTING_create_ambient();
MKZ_diffuse_component * MKZ_LIGHTING_create_diffuse();
MKZ_specular_component * MKZ_LIGHTING_create_specular();
MKZ_translucency_component* MKZ_LIGHTING_create_translucency();
MKZ_reflective_component * MKZ_LIGHTING_create_reflective();

void MKZ_LIGHTING_free_material(MKZ_material * mat);
void MKZ_LIGHTING_free_map(MKZ_map * map);
void MKZ_LIGHTING_free_3map(MKZ_3map * map3);
void MKZ_LIGHTING_free_cube_map(MKZ_cube_map * c_map);
void MKZ_LIGHTING_free_ambient(MKZ_ambient_component * ambient);
void MKZ_LIGHTING_free_diffuse(MKZ_diffuse_component * diffuse);
void MKZ_LIGHTING_free_specular(MKZ_specular_component * specular);
void MKZ_LIGHTING_free_translucency(MKZ_translucency_component * translucency);
void MKZ_LIGHTING_free_reflective(MKZ_reflective_component * reflective);
#endif /* LIB_MKZ_SRC_MKZ_LIGHTING_H_ */
