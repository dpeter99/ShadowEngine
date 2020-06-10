# What we have so far

I started this engine almost a year ago. It was the subject of 2 Uni assignments.
First it started as a c++ rewrite of my c 2d game/engine but quickly gown that scope. It currently has quite a few systems in place, like the Input, Entity and rendering. But I haven't had the chance to work on it for quite a while. I do remember that some parts need a rewrite (The input system for one) so first thing will be rediscovering some of the code and writing docs for the classes.

I did start a new dx12 renderer that would be more flexible and robust, than what we have currently. But I think that what we have currently a good enough dx12 renderer, so general housekeeping should be don first and leave the d3d12 branch alone for now.

The project uses premake to generate the vs solution files, so I did upgrade it form ``5.0.0-alpha13`` to ``5.0.0-alpha15`` and it still worked, so that is good.

The engine currently does not have any way to make ``apps`` ``games`` etc. So i will have to implement the possibility to write code that is not in the engine project.
