# Summary
I learned a lot by working on this project. In this file, I'll write about some things I've learned.

# List
* CMake
  * I used CMake before but never from scratch. It was pretty annoying to get it working but now I think I understand the basics.
* C++ templates
  * People usually define (not just declare) templated classes in headers because when a templated class is instantiated, you need all the definitions, not just declarations, to be monomorphized to the template.
* I learned how to set up GoogleTest and how to integrate it with CMake
* I experimented with C++'s execution policies but unfortunately Clang doesn't support them yet
* Debugging in VSCode. The debugger and CMake work together nicely in VSCode.
* Miscellaneous C++ things
  * It's annoying to have `const` member variables because if you do, you can't really do copy- or move-assignment. That's because the const member, after being set by the constructor, can never be changed. That's annoying because a lot of things rely on copy- or move-assignment.
    * I was unable to sort a vector of one of my classes because that class had a const member and sorting relies on move assignment.
    * References, even if they're not `const`, suffer from the same problem because changing a reference changes the thing that's being pointed to. You can't change what a reference points to, which is what you want to do in assignment if you have a member that's a reference.
      * This is a good reason to use raw pointers. The smart pointers involve ownership, which I didn't want my pointers to do. They're purely "observers" in my context, not owners. I don't want the object to be destroyed when my pointer dies so raw pointers were the right choice.
* How to enable and benefit from sanitizers
* At first, the only type of shape I had was Sphere and it was hard-coded everywhere: in World, Intersection, etc. Then I made an abstract Shape class that Sphere inherited from. Updating everything was a pain but I learned a lot about inheritance, virtual functions, polymorphism with pointers/references, etc.
* Unnamed parameter to indicate that you're deliberately not using it. You might still need the parameter because you're overriding a virtual function, for example.

# Interesting bugs
* I found intersections of spheres in a ranged for loop over a vector of spheres. My mistake was to take the spheres by copy (instead of by reference) in the for loop. Each intersection has a pointer to the sphere on which it's an intersection so with these copies, the pointers were to temporary spheres. That one took me a while to debug. Rust would prevent something like that with lifetimes.
  * This bug inspired me to look into sanitizers because they (specifically address sanitizer) can detect problems like this
* A point inside a sphere was shadowed but it shouldn't have been shadowed, because there was nothing between it and the light. The light was also inside the sphere.
  * It turns out that the problem was that my over-point (which is used to prevent self-shadowing) was using the wrong normal. If a point is inside an object, you negate the normal so that the lighting makes more sense, but I was setting the over-point before checking if the point was inside. So I used the original normal, and then later the normal was negated.
  * The solution was to set the over-point after checking whether the point is inside the object. That way, the over-point uses the correct normal.

# To do
* General cleanup
* Switch from headers to modules for fun & learning