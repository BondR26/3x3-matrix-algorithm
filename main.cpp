#include<iostream>
#include<vector>

void show_sum(std::vector<std::vector<int>>& sum)
{

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << sum[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

void show_matrix(std::vector<std::vector<int>>& matrix)
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << matrix[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

 void calculate_sums(std::vector<std::vector<int>>& s, std::vector<std::vector<int>>& sum)
 {
     int total = 0;

     for (int i = 0; i < 3; i++)
        {
            total = 0;

            for (int j = 0; j < 3; j++)
            {
                total += s[i][j];
            }

            sum[0][i] = total;

            total = 0;

            for (int j = 0; j < 3; j++)
            {
                total += s[j][i];
            }

            sum[1][i] = total;

     }
 }

 int find_the_location_of_black_sheep(std::vector<std::vector<int>> sum, std::vector<std::vector<int>> cube)
 {

     bool matrix_is_magical = true;

     int cost = 0;

    std::vector<std::vector<int>> cube_temp(3);
     for (int i = 0; i < 3; i++)
     {
         cube_temp[i].resize(3);

         for (int j = 0; j < 3; j++)
         {

             cube_temp[i][j] = cube[i][j];
         }
     }




     while (matrix_is_magical)//while matrix is not a magical thing
     {
         matrix_is_magical = false;

         for (int i = 0; i < 3; i++)
         {
             for (int j = 0; j < 3; j++)
             {
                 if (sum[0][i] != sum[1][j])
                 {
                     matrix_is_magical = true;

                     int direction = 1;

                     int temp = cube_temp[i][j];

                     int count = 6;

                     while (sum[0][i] != sum[1][j] and direction != 3)
                     {
                         for (int m = 0; m < 3; m++)
                         {
                             int vect = 1;


                             while (sum[0][i] != sum[1][j] and vect != 3)
                             {
                                 if (cube_temp[i][m] < 10 and vect == 1)
                                 {
                                     cube_temp[i][m] += 1;
                                 }
                                 else
                                 {
                                     vect = 2;
                                 }

                                 if (vect == 2 and cube_temp[i][m] > 0)
                                 {
                                     cube_temp[i][m] -= 1;
                                 }


                                 if (cube_temp[i][m] == 0)
                                 {
                                     cube_temp[i][m] = temp;//go back to original
                                     vect = 3;
                                 }

                                 calculate_sums(cube_temp, sum);

                             }
                         }

                         calculate_sums(cube_temp, sum);

                     }



                     //cost += std::abs(temp - cube_temp[i][j]);

                 }
             }
         }

     }

     show_matrix(cube);

     std::cout << "SUm after ->\n";

     show_sum(sum);

     show_matrix(cube_temp);


     for (int i = 0; i < 3; i++)
     {
         for (int j = 0; j < 3; j++)
         {
             if (cube_temp[i][j] != cube[i][j])
             {
                 cost += std::abs(cube_temp[i][j] - cube[i][j]);
                 cube[i][j] = cube_temp[i][j];
             }
         }
     }

     return cost;

 }



int formingMagicSquare(std::vector<std::vector<int>> s)
{
   
    std::vector<std::vector<int >> sum(2);

    sum[0].resize(3);
    sum[1].resize(3);

    bool flag = true;

    int cost = 0;//це те шо повинне повертатись (кількість змін якуі були внесені в числа шою квадрат став магічним)
    
    calculate_sums(s, sum);

    show_sum(sum);

    cost  = find_the_location_of_black_sheep(sum, s);

    return cost;
}



int main()
{

    //std::vector <std::vector<int>> s(3);

    int s[3][3] = { {4, 6 ,6 }, {2, 4 ,1 },{8, 9 ,8}};


    std::vector<std::vector <int>> cube(3); 
    for (int i = 0; i < 3; i++)
    {
        cube[i].resize(3);

        for (int j = 0; j < 3; j++)
        {
            cube[i][j] = s[i][j];
        }
    }
   
   /* for( int i = 0; i < 3; i++)
    {
        s[i].resize(3);

        for (int j = 0; j < 3; j++)
        {
            if(i==2 and j==2)
            s[i][j] = 4;
            else
                s[i][j] = 3;
        }
    }*/

    int result = formingMagicSquare(cube);

    std::cout << "it took cost of " << result << " to make matrix magical\n";
    std::cout << "Now magical cube look liket this ";
    show_matrix(cube);

    return EXIT_SUCCESS;
}