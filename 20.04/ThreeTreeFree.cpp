template< class T > struct TriTree {
  T val1, val2;
  TriTree< T > * lt, * mid, * rt;
};

template< class T >
void clear(TriTree< T > * root)
{
  if (!root) {
      return;
  }

  clear(root->rt);
  clear(root->lt);
  clear(root->mid);
  delete root;
}