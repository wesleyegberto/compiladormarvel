/**
*
*       Lista de Tokens e Palavras Chave
*/

/* Palavras reservadas da gramática */
#define FLOAT       256
#define INTEGER     257
#define PARAM       258
#define VECTOR      259
#define NUM         260
#define ID          261
#define FRAGMENT    262
#define ENDFRAGMENT 263
#define LITERAL     264
#define IF          265
#define ELSE        266
#define WHILE       267
#define WRITE       268
#define READ        269
#define CONSTANT    327

/* Símbolos da gramática */
#define OPENBRA     270 /* [ */
#define CLOSEBRA    271 /* ] */
#define COMMA       272 /* , */
#define ASSIGN      273 /* = */
#define OPENPAR     274 /* ( */
#define CLOSEPAR    275 /* ) */
#define NOT         276 /* ! */
#define PLUS        277 /* + */
#define MINUS       278 /* - */
#define EQUALS      279 /* == */
#define LT          280 /* < */ 
#define LE          281 /* <= */
#define GE          282 /* > */
#define GT          283 /* >= */
#define NE          284 /* != */
#define BITOR       285 /* | */
#define MULT        286 /* * */
#define DIV         287 /* / */
#define MOD         288 /* % */
#define BITAND      289 /* & */
#define AND         290 /* && */
#define OR          291 /* || */
#define SMCLN       292 /* ; */


/* Não Terminais */

#define Program                293
#define Statement_List         294
#define Statement_ListLinha    295
#define Statement              296
#define StatementLinha         297
#define StatementDuasLinhas    298
#define NameDecl               299
#define Fragment               300
#define Destiny                301
#define Expression             302
#define ExpressionLinha        303
#define ExpressionDuasLinhas   304
#define FragCall               305
#define Expr_List              306
#define Expr_ListLinha         307
#define ModifierList           308
#define ModifierListLinha      309
#define Id_List                310
#define Id_ListLinha           311
#define Simple_Expr            312
#define Simple_ExprLinha       313
#define Comp_Op                314
#define Rel_Op                 315
#define Modifier               316
#define Term                   317
#define TermLinha              318
#define Sign                   319
#define Add_Op                 320
#define Mult_Op                321
#define Factor                 322
#define FactorLinha            323
#define Bool_Exp               324
#define Bool_Or                325
#define Bool_And               326
/* fim Não Terminais */

