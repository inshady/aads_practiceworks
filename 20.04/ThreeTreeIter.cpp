template< class T > struct TriTree {
  T val0, val1;
  TriTree< T > * lt, * mid, * rt, * parent;
};

template< class T, class F > F traverse(TriTree< T > * root, F f)
{
  size_t ind = 0;

  if (!root) {
    return f;
  }

  while(root->lt) {
    root = root->lt;
  }
  
  while (root) {
    f(val0);
    f(val1);
    if (ind == 0) {
      if (root->mid) {
        root = root->mid;
        while(root->lt) {
          root = root->lt;
        }
      } else {
        ind = 1;
      }
    } else {
      if (root->rt) {
        root = root->rt;
        while(root->lt) {
          root = root->lt;
        }
        ind = 0;
      } else {
        TriTree< T > * parent = root->parent;
        while(parent) {
          if (parent->rt == root) {
            root = parent;
            parent = root->parent;
          } else if (parent->mid == root) {
            ind = 1;
            break;
          } else if (parent->lt == root) {
            ind = 0;
            break;
          }
        }
        root = parent;
      }
    }
  }

  return f;
}