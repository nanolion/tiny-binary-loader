# tiny-binary-loader
Read and write simple POD structs to binary files

# Example


~~~ c++
   /// struct must be composed of pod types
   /// such that sizeof() gives the proper size to load
   
   struct Pack
   {
      int a;
      int b;
   };
   
   File file( "new_file.bin", true, true );
   file.set_read_position(0);
   auto my_pack = file.read_buffer<Pack>()
~~~

