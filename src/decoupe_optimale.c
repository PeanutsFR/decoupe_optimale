/* decoupe_optimale.c */

/* envoyer le fichier à : guyslain.naves@univ-amu.fr */

#include <stdio.h>            /* C input/output                       */
#include <stdlib.h>           /* C standard library                   */
#include <glpk.h>        /* GNU GLPK linear/mixed integer solver */



/* COMPILATION MANUELLE */
/* gcc src/decoupe_optimale.c -lglpk -o decoupe_optimale */

int main(void) {

  /* declare variables */
  glp_prob *lp;
  int lig[1+200], col[1+200];
  double coeff[1+200], z, x1, x2, x3, x4;

    /* create problem */
  lp = glp_create_prob();
  glp_set_prob_name(lp, "decoupe_optimale");
  glp_set_obj_dir(lp, GLP_MIN);

    /* lines bounds */
  glp_add_rows(lp, 4);

  glp_set_row_name(lp, 1, "y1");
  glp_set_row_bnds(lp, 1, GLP_LO, 97.0, 0.0);

  glp_set_row_name(lp, 2, "y2");
  glp_set_row_bnds(lp, 2, GLP_LO, 610.0, 0.0);

  glp_set_row_name(lp, 3, "y3");
  glp_set_row_bnds(lp, 3, GLP_LO, 395.0, 0.0);

  glp_set_row_name(lp, 4, "y4");
  glp_set_row_bnds(lp, 4, GLP_LO, 211.0, 0.0);


  /* function objective */
  glp_add_cols(lp, 4);

  glp_set_col_name(lp, 1, "x1");
  glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);
  glp_set_obj_coef(lp, 1, 1.0);

  glp_set_col_name(lp, 2, "x2");
  glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);
  glp_set_obj_coef(lp, 2, 1.0);

  glp_set_col_name(lp, 3, "x3");
  glp_set_col_bnds(lp, 3, GLP_LO, 0.0, 0.0);
  glp_set_obj_coef(lp, 3, 1.0);

  glp_set_col_name(lp, 4, "x4");
  glp_set_col_bnds(lp, 4, GLP_LO, 0.0, 0.0);
  glp_set_obj_coef(lp, 4, 1.0);

  /* matrix */
  /* pour mettre à jour les champs voulus, on fera :
    i -> (i-1)%4 + 1
    i -> (3+i)/4 */

  /* ligne 1 */
  lig[1] = 1, col[1] = 1, coeff[1] = 2; // 2 x1
  lig[2] = 1, col[2] = 2, coeff[2] = 0; // 0 x2
  lig[3] = 1, col[3] = 3, coeff[3] = 0; // 0 x3
  lig[4] = 1, col[4] = 4, coeff[4] = 0; // 0 x4

  /* ligne 2 */
  lig[5] = 2, col[5] = 1, coeff[5] = 0;
  lig[6] = 2, col[6] = 2, coeff[6] = 2;
  lig[7] = 2, col[7] = 3, coeff[7] = 0;
  lig[8] = 2, col[8] = 4, coeff[8] = 0;

  /* ligne 3 */
  lig[9] = 3, col[9] = 1, coeff[9] = 0;
  lig[10] = 3, col[10] = 2, coeff[10] = 0;
  lig[11] = 3, col[11] = 3, coeff[11] = 3;
  lig[12] = 3, col[12] = 4, coeff[12] = 0;

  /* ligne 4*/
  lig[13] = 4, col[13] = 1, coeff[13] = 0;
  lig[14] = 4, col[14] = 2, coeff[14] = 0;
  lig[15] = 4, col[15] = 3, coeff[15] = 0;
  lig[16] = 4, col[16] = 4, coeff[16] = 7;

  glp_load_matrix(lp, 16, lig, col, coeff);

  /* solve problem */
  glp_simplex(lp, NULL);

  /* recover and display result */
  z = glp_get_obj_val(lp);
  x1 = glp_get_col_prim(lp, 1);
  x2 = glp_get_col_prim(lp, 2);
  x3 = glp_get_col_prim(lp, 3);
  x4 = glp_get_col_prim(lp, 4);

  printf("z = %g; x1 = %g; x2 = %g; x3 = %g; x4 = %g\n", z, x1, x2, x3, x4);

  /* housekeeping */
  glp_delete_prob(lp);
  glp_free_env();


  return 0;

}

