#include <iostream>
#include <list>
#include <string>
using namespace std;

list<string> print(int n)
{
   string* names = new string[n];
   string names_sort;
   for (int i=0; i<n; i++){
        std::cin >> names[i];
    }

    for (int i=0; i<n-1; i++){
        for (int j=i+1; j<n; j++){
            if (names[i]>names[j])
            {
                names_sort=names[i];
                names[i]=names[j];
                names[j]=names_sort;

            }
        }

    }

    std::list<string> listt;
    listt.insert(listt.begin(),names,names+n);
    std::list <string> :: iterator it;

  for (it = listt.begin(); it != listt.end(); it++) {
    std::cout << (*it) << " ";
    }
    std::cout << '\n';
return listt;
}

void result(list<string>list1,list<string>list2){          //результирующий список
  list1.merge(list2);
  std::list <string> :: iterator it1;
  for (it1 = list1.begin(); it1 != list1.end(); it1++) {
    std::cout << (*it1) << " ";
  }
  std::cout << '\n';

  list1.unique();

  for (it1 = list1.begin(); it1 != list1.end(); it1++) {
    std::cout << (*it1) << " ";
  }
  std::cout << '\n';

}

int main()
{
    std::list<string> list1;
    std::list<string> list2;
    int n1, n2;
    std::cout << "Маша, введи количество друзей: " << endl << ">";
    std::cin >> n1;
    list1=print(n1);
    std::cout << "Миша, введи количество друзей: " << endl << ">";
    std::cin >> n2;
    list2=print(n2);
    result(list1, list2);
return 0;
}
