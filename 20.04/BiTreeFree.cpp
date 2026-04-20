template< class T > struct BiTree {
    T val;
    BiTree< T > * lt, * rt;
};

template< class T >
void clear(BiTree< T > * root)
{
  if (!root) {
      return;
  }

  clear(root->rt);
  clear(root->lt);
  delete root;
}