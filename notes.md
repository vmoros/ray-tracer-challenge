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

# Interesting bugs
* I found intersections of spheres in a ranged for loop over a vector of spheres. My mistake was to take the spheres by copy (instead of by reference) in the for loop. Each intersection has a pointer to the sphere on which it's an intersection so with these copies, the pointers were to temporary spheres. That one took me a while to debug. Rust would prevent something like that with lifetimes.