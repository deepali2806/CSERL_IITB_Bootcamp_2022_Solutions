#include "http_server.hh"

#include <vector>

#include <sys/stat.h>

#include <fstream>
#include <sstream>
#include <dirent.h>
#define BLOCKSIZE 100

using namespace std;

string splitDynamicStr(string s) {
//<name> in the request is sent as %3Cname%3F --> So converting it accordingly
  string newStr = s.substr(3,s.length()-6);
  return newStr;
}

int fibonacci(int n)
{
   if (n <= 1) {
        return n;
    }
 
    int prev = 0, curr = 1;
    for (int i = 0; i < n - 1; i++)
    {
        int newFib = prev + curr;
        prev = curr;
        curr = newFib;
    }
 
    return curr;
}

vector<string> split(const string &s, char delim) {
  vector<string> elems;

  stringstream ss(s);
  string item;

  while (getline(ss, item, delim)) {
    if (!item.empty())
      elems.push_back(item);
  }

  return elems;
}

HTTP_Request::HTTP_Request(string request) {
  vector<string> lines = split(request, '\n');
  vector<string> first_line = split(lines[0], ' ');

  this->HTTP_version = "1.0"; // We'll be using 1.0 irrespective of the request

  /*
   TODO : extract the request method and URL from first_line here
  */
  this->method = first_line[0];
  this->url = first_line[1];

  if (this->method != "GET") {
    cerr << "Method '" << this->method << "' not supported" << endl;
    exit(1);
  }
}

HTTP_Response *handle_request(string req) {
  HTTP_Request *request = new HTTP_Request(req);

  HTTP_Response *response = new HTTP_Response();

  vector<string> check_url = split(request->url, '?');
  if (check_url[0] == "/fib" || check_url[0] == "/hello")
  {
    if(check_url[0] == "/hello")
    {
      string arg = splitDynamicStr(check_url[1]);
      response->HTTP_version = "HTTP/1.0";
      response->status_code = "200";
      response->status_text = "OK";
      response->content_type = "text/html";
      
      string responseBody = "<html> <h2> Hello " + arg + "!</h2> </html>";
      response->content_length = to_string(responseBody.length());
      response->body = responseBody;
      
      cout<<"\nArgument is :"<<arg<<endl;
      delete request;
      return response;    
    }
    else if(check_url[0] == "/fib")
    {
        string arg = splitDynamicStr(check_url[1]);
        response->HTTP_version = "HTTP/1.0";
        response->status_code = "200";
        response->status_text = "OK";
        response->content_type = "text/html";
        int ans = fibonacci(stoi(arg));
        string responseBody = "<html> <h2> The "+ arg +"th Fibonacci number is " + to_string(ans) + "!</h2> </html>";
        response->content_length = to_string(responseBody.length());
        response->body = responseBody;
        
        cout<<"\nArgument is :"<<arg<<endl;
        delete request;
        return response; 
    }
    
  }
  else
  {
      string url = string("html_files") + request->url;
      response->HTTP_version = "HTTP/1.0";
      struct stat sb;
      if (stat(url.c_str(), &sb) == 0) // requested path exists
      {
        response->status_code = "200";
        response->status_text = "OK";
        response->content_type = "text/html";

        string body;

        if (S_ISDIR(sb.st_mode)) {
          /*
          In this case, requested path is a directory.
          TODO : find the index.html file in that directory (modify the url
          accordingly)
          */ 
          DIR *dir;
          struct dirent *ent;
          if ((dir = opendir (url.c_str())) != NULL) {
            /* print all the files and directories within directory */
            while ((ent = readdir (dir)) != NULL) {
              printf ("%s\n", ent->d_name);
              if(ent->d_name == "index.html")
              {
                url = url + string("index.html");
              }
            }
            closedir (dir);
          }

        }

        /*
        TODO : open the file and read its contents
        */
          cout<<"\n\nURL:: "<< url <<endl;
          ifstream fin;
          string line;
          string responseBody;
          fin.open(url);
          
          while (fin) {
            // Read a Line from File
            getline(fin, line);
            responseBody = responseBody + line;
            // Print line in Console
            //cout << line << endl;
          }
            //cout<<"Printing File contents"<<endl;
          // cout<<" :- "<<responseBody<<endl;
        /*
        TODO : set the remaining fields of response appropriately
        */
          response->content_length =  to_string(responseBody.length());
          response->body = responseBody;
          delete request;

          return response;
    }
    else {
      /*
      TODO : set the remaining fields of response appropriately
      */
      response->status_code = "404";
      response->status_text = "Page not found";
      response->content_type = "text/html";

      string responseBody ="Page Not Found :-)";
      response->content_length =  to_string(responseBody.length());
      response->body = responseBody;
      delete request;

      return response;
    }
  }

      //Else show 404
      response->status_code = "404";
      response->status_text = "Page not found";
      response->content_type = "text/html";

      string responseBody ="Page Not Found :-)";
      response->content_length =  to_string(responseBody.length());
      response->body = responseBody;
      delete request;

      return response;
}

string HTTP_Response::get_string() {
  /*
  TODO : implement this function
  */
  string responseString = this->HTTP_version + " " + this->status_code + " " + this->status_text + "\r\n"
		      + "Content-Type: " + this->content_type + "\r\n" 
		      + "Content-Length: " + this->content_length + "\r\n\r\n"
		      + this->body;
  return responseString;
}
