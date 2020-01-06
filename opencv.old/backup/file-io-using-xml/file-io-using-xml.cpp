#include <opencv2/core.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

class Data
{
public:   int a;
public:   double x;
public:   string id;
public:   Data() : a(0), x(0), id() {}
public:   explicit Data(int) : a(97), x(CV_PI), id("mydata1234") {}
public:   void write(FileStorage & fs) const
          {
            fs << "{" << "a" << a << "x" << x << "id" << id << "}";
          }
public:   void read(const FileNode & node)
          {
            a = (int) node["A"];
            x = (double) node["x"];
            id = (string) node["id"];
          }
};

static void write(FileStorage & fs, const std::string &, const Data & x)
{
  x.write(fs);
}

static void read(const FileNode & node, Data & x, const Data & default_value = Data())
{
  if(node.empty())
  {
    x = default_value;
  }
  else
  {
    x.read(node);
  }
}

static ostream & operator<<(ostream & out, const Data & m)
{
  out << "{ id = " << m.id << ", ";
  out << "x = " << m.x << ", ";
  out << "a = " << m.a << "}";
  return out;
}

int main(void)
{
  string filename = "anise.yaml";
  Mat R = Mat_<uchar>::eye(3, 3);
  Mat T = Mat_<double>::zeros(3, 1);
  Data m(1);
  // write
  {
    FileStorage fs(filename, FileStorage::WRITE);

    fs << "iterationNr" << 100;
    fs << "strings" << "[";
    fs << "image1.jpg" << "Awesomeness" << "../data/baboon.jpg";
    fs << "]";

    fs << "Mapping";
    fs << "{" << "One" << 1;
    fs <<        "Two" << 2 << "}";

    fs << "R" << R;
    fs << "T" << T;

    fs << "Data" << m;

    fs.release();
    cout << "Write Done." << endl;
  }
  // read
  {
    cout << endl << "Reading: " << endl;
    FileStorage fs;
    fs.open(filename, FileStorage::READ);

    int iterationNr = (int) fs["iterationNr"];
    if(!fs.isOpened())
    {
      cerr << "Failed to opened" << filename << endl;
      return 1;
    }

    FileNode n = fs["strings"];
    if(n.type() != FileNode::SEQ)
    {
      cerr << "strings is not a sequence!" << endl;
      return 1;
    }

    for(FileNodeIterator it = n.begin(); it != n.end(); ++it)
    {
      cout << (string) *it << endl;
    }

    n = fs["Mapping"];
    cout << "Two " << (int)(n["Two"]) << "; ";
    cout << "One " << (int)(n["One"]) << endl << endl;

    Data m;
    Mat R;
    Mat T;

    fs["R"] >> R;
    fs["T"] >> T;
    fs["Data"] >> m;

    cout << endl
         << "R = " << R << endl
         << "T = " << T << endl << endl
         << "Data = " << endl << m << endl << endl;

    cout << "attempty to read non existing (should initialize the data structure with its default).";
    fs["NonExisting"] >> m;
    cout << endl << "NonExisting = " << endl << m << endl;
  }
  cout << endl
       << "Tip: Open up " << filename << "with a text editor to see the serialized data." << endl;
}
