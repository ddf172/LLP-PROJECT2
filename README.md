BMP File Analyzer and Processor
Note: This is a basic academic project developed for educational purposes.

Features:
- Parse and display BMP file headers (BITMAPFILEHEADER and BITMAPINFOHEADER)
  ./bmp_analyzer <path_to_bmp_file>
- Generate RGB color histograms for 24-bit uncompressed BMP files
- Convert color BMP images to grayscale
  ./bmp_analyzer <path_to_input_bmp> <path_to_output_bmp>
- Hide and retrieve text messages in BMP files using steganography
  Decoding message: ./bmp_analyzer <path_to_input_bmp> <path_to_encoded_bmp> "text to be hidden"
  Encoding message: ./bmp_analyzer <path_to_encoded_bmp>

Limitations:
The histogram and grayscale conversion features only support uncompressed 24-bit BMP files.
The steganography feature has a maximum message length of 255 characters.
