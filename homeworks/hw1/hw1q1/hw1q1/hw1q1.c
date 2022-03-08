#include <stdio.h>
#include <math.h>

#define ZERO 0.000001

int main() {
    double a, b, c;
    int responseLength;

    do {
        // Get user input
        printf("Enter the coefficients of a polynomial:\n");
        responseLength = scanf("%lf%lf%lf", &a, &b, &c);

        // Testing input validity
        if(responseLength != 3) {
            return 0;
        }
    } while(a < ZERO && a > -ZERO);

    // Calculating the discriminant and making sure that it's positive
    double discriminant = b*b-4*a*c;

    if(discriminant < -ZERO) {
        printf("There are no roots");
    } else {
        // Calculating the positive root value
        double root1 = (-b + sqrt(discriminant))/(2*a);
        if(root1 < ZERO && root1 > -ZERO) {
            root1 = 0;
        }

        // If the discriminant is zero
        if(discriminant < ZERO && discriminant > -ZERO) {
            printf("The root is %.3f", root1);
        } else {
            // Calculating the negative root value
            double root2 = (-b - sqrt(discriminant))/(2*a);
            if(root2 < ZERO && root2 > -ZERO) {
                root2 = 0;
            }

            if(root1 < root2) {
                printf("The roots are %.3f, %.3f", root1, root2);
            } else {
                printf("The roots are %.3f, %.3f", root2, root1);
            }

        }
    }
    return 0;
}
