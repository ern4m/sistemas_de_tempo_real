int main ()
{
    SymExpr x = sym_placeholder("x");
    SymExpr expr = sym_mult(x, x);

    sym_print(expr);     printf("\n");

    SymExpr df = sym_deriv("x", expr);

    sym_print(df);          printf("\n");

    sym_free(df);
    sym_free(expr);
    sym_free(x);

    return 0;
}
