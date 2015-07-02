# tiny-binary-loader
Read and write simple POD structs to binary files

# Example


~~~ c
   /// Example:
   /// struct must be composed of pod types
   /// such that sizeof() gives the proper size to load
   struct Pack
   {
      int a;
      int b;
   };
   file.set_read_position(0);
   auto my_pack = file.read_buffer<Pack>()
~~~

