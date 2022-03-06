# DX12 Shaders 

The engine currently supports DXC as the shader compiler (SM 5.0+ mainly 6.4). The engine does support dynamic extraction of the material data. 

## Material data
All the material data that is not textures (int float vec3 etc.) are have to be stored in a single ``cbuffer``. And the name has to start with ``Mat_``. This will be found and boud at runtime.

All the textures must have the name start with ``Mat_``. 

### Root sig.
In the root signaure the ``Mat_`` properties have to be inside a top level descriptor table.