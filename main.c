#include "pro.h"

int main() {
    int n;
    EdgeList *Net;
    int* Prim;
    EdgeList *PrimPath;
    int first,last;

    scanf("%d",&n);
    if (n<=0) {
        printf("Invalid Input\n");
        return 0;
    }

    Net = build_net(n);

    Prim = build_prim_tree(Net,n);
    PrimPath=build_paths(Prim,n);

    scanf("%d%d",&first,&last);
    find_and_print_path(PrimPath,n,first,last);

    free_net(Net,n);
    free_paths(PrimPath,n);

    return 0;
}