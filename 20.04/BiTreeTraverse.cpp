template< class T > struct BiTree {
    T val;
    BiTree< T > * lt, * rt, * parent;
};


template< class T > BiTree< T > * toLeft(BiTree< T > * root)
{
  if (!root) {
    return root;
  }

  while(root->lt) {
    root = root->lt;
  }
}

template< class T > BiTree< T > * toRight(BiTree< T > * root)
{
  if (!root) {
    return root;
  }

  while(root->rt) {
    root = root->rt;
  }
}

template< class T, class F > F traverseUp(BiTree< T > * root, F f)
{
  while(root) {
    f(root->val);
    if (root->rt) {
        root = root->rt;
        root = toLeft(root);
    } else {
      BiTree< T > * parent = root->parent;
      while(parent && parent->lt != root) {
        root = parent;
        parent = root->parent;
      }
      root = parent;
    }
  }

  return f;
}

template< class T, class F > F traverseDown(BiTree< T > * root, F f)
{
  while(root) {
    f(root->val);
    if (root->lt) {
        root = root->lt;
        root = toRight(root);
    } else {
      BiTree< T > * parent = root->parent;
      while(parent && parent->rt != root) {
        root = parent;
        parent = root->parent;
      }
      root = parent;
    }
  }

  return f;
}

template< class T > struct BiTreeIt {
  BiTree< T > * curr;
};

template< class T > T& value(BiTreeIt< T > it)
{
  return it.curr->val;
}

template< class T > BiTreeIt< T > next(BiTreeIt< T > it)
{
  if (it.curr->rt) {
    it.curr = it.curr->rt;
    it.curr = toLeft(it.curr);
  } else {
    BiTree< T > * parent = it.curr->parent;
    while(parent && parent->lt != it.curr) {
      it.curr = parent;
      parent = it.curr->parent;
    }
    it.curr = parent;
  }
  return it;
}

template< class T > BiTreeIt< T > prev(BiTreeIt< T > it)
{
  if (it.curr->lt) {
    it.curr = it.curr->lt;
    it.curr = toRight(it.curr);
  } else {
    BiTree< T > * parent = it.curr->parent;
    while(parent && parent->rt != it.curr) {
      it.curr = parent;
      parent = it.curr->parent;
    }
    it.curr = parent;
  }

  return it;
}

template< class T > bool hasNext(BiTreeIt< T > it)
{
  return next(it);
}

template< class T > bool hasPrev(BiTreeIt< T > it)
{
  return prev(it);
}

