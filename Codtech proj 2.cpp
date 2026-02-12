#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
mutex mtx;

// ---------- SIMPLE RLE COMPRESSION ----------
string compressRLE(const string &data) {
    string result = "";

    for (size_t i = 0; i < data.size(); i++) {
        int count = 1;

        while (i + 1 < data.size() && data[i] == data[i + 1]) {
            count++;
            i++;
        }

        result += data[i];
        result += to_string(count);
    }
    return result;
}

// ---------- RLE DECOMPRESSION ----------
string decompressRLE(const string &data) {
    string result = "";

    for (size_t i = 0; i < data.size(); i++) {
        char ch = data[i];
        i++;

        string num = "";
        while (i < data.size() && isdigit(data[i])) {
            num += data[i];
            i++;
        }
        i--;

        int count = stoi(num);
        result.append(count, ch);
    }

    return result;
}

// ---------- THREAD WORK ----------
void compressChunk(string chunk, vector<string>& output, int index) {

    string compressed = compressRLE(chunk);

    lock_guard<mutex> lock(mtx);
    output[index] = compressed;
}

// ---------- MULTITHREADED COMPRESSION ----------
void multiThreadCompress(string inputFile, string outputFile, int threadsCount) {

    ifstream in(inputFile);
    ofstream out(outputFile);

    string data((istreambuf_iterator<char>(in)),
                 istreambuf_iterator<char>());

    int size = data.size();
    int part = size / threadsCount;

    vector<string> results(threadsCount);
    vector<thread> threads;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < threadsCount; i++) {

        int begin = i * part;
        int end = (i == threadsCount - 1) ? size : (i + 1) * part;

        string chunk = data.substr(begin, end - begin);

        threads.push_back(thread(compressChunk, chunk, ref(results), i));
    }

    for (auto &t : threads)
        t.join();

    for (auto &s : results)
        out << s;

    auto stop = chrono::high_resolution_clock::now();

    cout << "Multithread Compression Time: "
         << chrono::duration<double>(stop - start).count()
         << " seconds\n";
}

// ---------- SINGLE THREAD FOR COMPARISON ----------
void singleThreadCompress(string inputFile, string outputFile) {

    ifstream in(inputFile);
    ofstream out(outputFile);

    string data((istreambuf_iterator<char>(in)),
                 istreambuf_iterator<char>());

    auto start = chrono::high_resolution_clock::now();

    string result = compressRLE(data);

    auto stop = chrono::high_resolution_clock::now();

    out << result;

    cout << "Single Thread Time: "
         << chrono::duration<double>(stop - start).count()
         << " seconds\n";
}

// ---------- DECOMPRESS ----------
void decompressFile(string inputFile, string outputFile) {

    ifstream in(inputFile);
    ofstream out(outputFile);

    string data((istreambuf_iterator<char>(in)),
                 istreambuf_iterator<char>());

    string result = decompressRLE(data);

    out << result;

    cout << "Decompression completed.\n";
}

// ---------------- MAIN ----------------
int main() {

    int choice;
    string in, out;

    while (true) {

        cout << "\n==== Multithreaded Compression Tool ====\n";
        cout << "1. Compress (Single Thread)\n";
        cout << "2. Compress (Multi Thread)\n";
        cout << "3. Decompress\n";
        cout << "4. Exit\n";
        cout << "Choice: ";

        cin >> choice;

        if (choice == 4) break;

        cout << "Input file: ";
        cin >> in;

        cout << "Output file: ";
        cin >> out;

        switch (choice) {

            case 1:
                singleThreadCompress(in, out);
                break;

            case 2: {
                int t;
                cout << "Enter threads count: ";
                cin >> t;
                multiThreadCompress(in, out, t);
                break;
            }

            case 3:
                decompressFile(in, out);
                break;

            default:
                cout << "Invalid!\n";
        }
    }

    return 0;
}

