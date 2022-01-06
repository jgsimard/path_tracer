# Toy Path Tracer

This is an toy path tracer implementation in C++. I based this implementation on the **Ray Tracing in One Weekend** series (https://raytracing.github.io/) as a starting point. I want to implement as many features from the book **Physically Based Rendering** (https://www.pbrt.org/). when I feel like enough features are implemented in C++, I want to build a Cuda backend

## Implementation Goals in C++

* BVH faster version
  * SHA optimization
* Textures
* Use Explicit MonteCarlo Sampler/integrators
* Material/BSDF Sampling
* Lignt Sampling
* Multiple Importance Sampling (MIS)
* Phong BRDF
* Blinn-Phong BRDF
* Participating media
* Bidirectional Path Tracing
* Photon mapping !!!
  * Basic Version
  * Improved Version
  * Progressive Photon mapping
  * Volumetric Photon mapping

I thinks this is an ambitious goal list, it might take years to implement because I have other stuff to do...
 



## Implementation Goals in Cuda
### I plan to start this when the MIS is done in pure C++
* BVH
  * Basic implementation
  * SHA optimization
* Textures
* Use Explicit MonteCarlo Sampler/integrators
* Material/BSDF Sampling
* Lignt Sampling
* Multiple Importance Sampling (MIS)
* Phong BRDF
* Blinn-Phong BRDF
* Participating media
* Bidirectional Path Tracing
* Photon mapping !!!
  * Basic Version
  * Improved Version
  * Progressive Photon mapping
  * Volumetric Photon mapping