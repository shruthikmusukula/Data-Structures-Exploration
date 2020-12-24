#include "queue.h"

int main()
{
  queue<int> q(3);
  cout << "Queue size is " << q.size() << endl;
  cout << "\n";

  q.push(1);
  q.push(2);
  q.push(3);
  cout << "Top element is: " << q.peek() << endl;
  cout << "Queue size is " << q.size() << endl;
  cout << q;
  cout << "\n";

  q.pop();
  q.pop();
  cout << "Top element is: " << q.peek() << endl;
  cout << "Queue size is " << q.size() << endl;
  cout << q;
  cout << "\n";

  q.pop();
  if (q.isEmpty())
    cout << "Queue Is Empty\n";
  else
    cout << "Queue Is Not Empty\n";
  cout << "\n";

  q.push(1);
  q.push(2);
  q.push(3);
  q.push(4);
  q.push(5);
  cout << "Top element is: " << q.peek() << endl;
  cout << "Queue size is " << q.size() << endl;
  cout << q;
  cout << "\n";

  q.pop();
  q.pop();
  cout << "Top element is: " << q.peek() << endl;
  cout << "Queue size is " << q.size() << endl;
  cout << q;

  return 0;
}