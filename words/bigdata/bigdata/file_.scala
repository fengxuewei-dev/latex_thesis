import java.io.PrintWriter
val out = new PrintWriter("test_file.txt")
out.println("hello world")
out.println("Spark is good")
out.close()


import scala.io.Source
val lines = in.getLines // 返回的是一个迭代器，获得文件中的所有行
for(line <- lines) println(line)  // 获得 每一行的数据，且打印
