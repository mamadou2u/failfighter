#ifndef ENNEMI_H
#define ENNEMI_H
#define esize_haut 80
int  frame=0;
struct ennemi
{
  int right;
  int left;
}en;

void fonckick();
void fonckickr();
void foncavancer();
void foncavancerr();
void setforwarde();
void setforwardre();
void setkicke();
void setkickre();
void setstatic();
void foncstatic();
void foncstaticr();
#endif /* ENNEMI_H */
