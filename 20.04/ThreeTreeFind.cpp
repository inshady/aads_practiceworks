template< class T > struct TriTree {
  T val1, val2;
  TriTree< T > * lt, * mid, * rt;
};

template< class T, class Cmp >
const TriTree< T > * find(const T& d, const TriTree< T > * root, Cmp cmp)
{
  while (root) {
    if (cmp(root->val1, d)) {
      if (cmp(root->val2, d)) {
        root = root->rt;
      } else if (cmp(d, root->val2)) {
        root = root->mid;
      } else {
        return root;
      }
    } else if (cmp(d, root->val1)) {
      root = root->lt;
    } else {
      return root;
    }
  }
  return root;
}