# MULTITHREADED-FILE-COMPRESSION-TOOL

*COMPANY*: CODTECH IT SOLUTIONS

*NAME*: R V DHARANI

*INTERN-ID*: CTIS3468

*DOMAIN*: C++ PROGRAMMING

*DURATION*: 4 WEEKS

*MENTOR*: NEELA SANTHOSH

The Multithreaded File Compression Tool is a C++ based application designed to demonstrate the concepts of file handling, data compression, multithreading, synchronization, and performance comparison between single-threaded and multi-threaded execution. The primary objective of this project is to compress and decompress text files using a simple compression algorithm while analyzing the performance benefits of parallel processing.

The compression algorithm implemented in this project is Run-Length Encoding (RLE). RLE is a basic lossless data compression technique that reduces file size by replacing consecutive repeated characters with a single character followed by its count. For example, the string “aaabbc” would be compressed to “a3b2c1”. Although RLE is not as advanced as real-world compression algorithms like ZIP or Huffman coding, it is simple to implement and clearly demonstrates how compression works at a conceptual level. The tool also includes a decompression function that restores the compressed data back to its original form, ensuring correctness and reversibility.

One of the key features of this project is the implementation of multithreading using the C++ Standard Library <thread> module. In the single-threaded compression mode, the entire file is read into memory and compressed sequentially. This serves as a baseline for performance comparison. In contrast, the multithreaded compression mode divides the input file into equal-sized chunks based on the number of threads specified by the user. Each chunk is processed independently by a separate thread. This allows multiple parts of the file to be compressed simultaneously, potentially reducing overall execution time on multi-core systems.

To ensure safe access to shared resources during multithreaded execution, a mutex (std::mutex) is used. Since multiple threads write their compressed results into a shared vector, synchronization is necessary to prevent race conditions and data corruption. The lock_guard mechanism ensures that only one thread writes to the shared output structure at a time. This demonstrates practical use of thread synchronization and safe concurrent programming.

The tool also measures execution time using the <chrono> library. By capturing timestamps before and after compression, the program calculates and displays the time taken for both single-threaded and multithreaded execution. This allows users to compare performance and understand how parallel processing can improve efficiency for larger files. For small input files, the time difference may not be noticeable due to the speed of modern processors, but for larger datasets, multithreading can provide significant improvement.

The program provides a menu-driven interface, making it user-friendly and interactive. Users can choose between single-thread compression, multi-thread compression, decompression, or exiting the application. This structured approach makes the tool easy to test and demonstrates good program organization and modular design.

From a learning perspective, this project integrates multiple core concepts of C++ programming:

File input/output using ifstream and ofstream

String manipulation and data processing

Multithreading and parallel execution

Mutex-based synchronization

Performance measurement using high-resolution clocks

Modular function design and structured programming

The project is suitable for academic demonstrations in operating systems, system programming, and data structures courses. It highlights how computational tasks can be divided and executed concurrently to improve performance. Although the compression algorithm used is simple, the architectural design reflects real-world parallel processing systems where workloads are distributed among multiple processing units.

In conclusion, the Multithreaded File Compression Tool effectively demonstrates the practical implementation of file compression and parallel programming in C++. It combines algorithmic logic, concurrency control, and performance benchmarking into a single cohesive application. This project not only showcases technical proficiency in C++ but also provides insight into how modern software leverages multithreading to optimize performance.
