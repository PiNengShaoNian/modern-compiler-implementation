#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct tree *T_tree;
typedef char * String;
struct tree {
    void *binding;
    String key;
    T_tree left;
    T_tree right;
};

T_tree Tree(T_tree l, String key, T_tree r, void *binding) {
    T_tree t = malloc(sizeof(struct tree));
    t->binding = binding;
    t->key = key;
    t->left = l;
    t->right = r;
    return t;
}

T_tree insert(String key, void *binding, T_tree t) {
    if(t == NULL) return Tree(NULL, key, NULL, binding);
    else if(strcmp(key, t->key) < 0) {
         return Tree(insert(key, binding, t->left), t->key, t->right, t->binding);
    } else {
        return Tree(t->left, t->key, insert(key, binding, t->right), t->binding);
    }
}

void* lookup(String key, T_tree t) {
    if(t == NULL) return NULL;
    else if(strcmp(key, t->key) == 0) return t->binding;
    else if(strcmp(key, t->key) < 0) return lookup(key, t->left);
    else return lookup(key, t->right);
}

int main() {
    T_tree t = NULL;
    t = insert("a", "a", t);
    t = insert("b", "b", t);
    t = insert("c", "c", t);
    t = insert("d", "d", t);

    assert(lookup("a", t) == "a");
    assert(lookup("b", t) == "b");
    assert(lookup("c", t) == "c");
    assert(lookup("d", t) == "d");
    assert(lookup("e", t) == NULL);
}