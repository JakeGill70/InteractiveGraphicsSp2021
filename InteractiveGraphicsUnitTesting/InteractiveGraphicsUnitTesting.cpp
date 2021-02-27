#include "pch.h"
#include "CppUnitTest.h"
#include "../InteractiveGraphicsSp2021/BaseObject.cpp"
#include "../InteractiveGraphicsSp2021/AbstractReader.cpp"
#include "../InteractiveGraphicsSp2021/TextFileReader.cpp"
#include <fstream>
using std::ofstream;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace InteractiveGraphicsUnitTesting
{
   TEST_CLASS(ATextFileReader)
   {
   public:

      TEST_METHOD(ShouldHaveAnErrorIfTheFileWasNotFound)
      {
         TextFileReader sut("NoSuchFile.txt");
         sut.Open();
         Assert::IsTrue(sut.HasError());
      }

      TEST_METHOD(ShouldReportTheContentsOfAnExistingFile)
      {
         ofstream fout("TestFile.txt");
         fout << "Content Line 1" << std::endl
            << "Content Line 2" << std::endl;
         fout.close();

         TextFileReader sut("TestFile.txt");
         sut.Open();
         Assert::IsFalse(sut.HasError());
         sut.Read();
         string expected("Content Line 1\nContent Line 2\n");
         Assert::AreEqual(expected, sut.GetContents());

         std::remove("TestFile.txt");
      }
   };
}
