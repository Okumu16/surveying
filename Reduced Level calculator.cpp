#include <iostream>//Includes the standard input/output library
#include <cmath>//include the math library for mathematical functions
#include <iomanip>//includes the input/ouput manipulation library for formating output

using namespace std;//Allows using the standard library functions without specifying the namespace 

//Function to calculate Height of collimation
double calculateHOC(double benchmarkRl, double backsight)
{
    //height of collimation is the sum of benchmark reduced level and backsight
    return benchmarkRl + backsight;
}

//Function to calculate the reduced level based on the height of collimation
//sight reading and whether it's a backsight or a foresight.
double calculateRL(double hoc, double sight, bool isBacksight)
{
    return isBacksight ?  : hoc - sight;//Reduced level is the difference between the height of collimation and sight(intersight or foresight)
}

void groupName()
{
    //This displays the name of the group (GROUP 9) as the heading of the program
    cout<<"\n\n";
    cout<<"    "<<"  ***  "<<"  *****   "<<"    ***  "<<"  **    **"<<"  *****  "<<"     ***  "<<endl;
    cout<<"    "<<" ***** "<<"  ******  "<<"   ***** "<<"  **    **"<<"  ****** "<<"    ******"<<endl;
    cout<<"    "<<"**   **"<<"  **   ** "<<"  **   **"<<"  **    **"<<"  **   **"<<"   **   **"<<endl;
    cout<<"    "<<"**     "<<"  **   ** "<<"  **   **"<<"  **    **"<<"  **   **"<<"   **   **"<<endl;
    cout<<"    "<<"**     "<<"  ******  "<<"  **   **"<<"  **    **"<<"  ** **  "<<"    ******"<<endl;
    cout<<"    "<<"** ****"<<"  **   ** "<<"  **   **"<<"  **    **"<<"  **     "<<"        **"<<endl;
    cout<<"    "<<"**   **"<<"  **   ** "<<"  **   **"<<"  **    **"<<"  **     "<<"   **   **"<<endl;
    cout<<"    "<<" ***** "<<"  **   ** "<<"   ***** "<<"   ****** "<<"  **     "<<"    ******"<<endl;
    cout<<"    "<<"  ***  "<<"  **   ** "<<"    ***  "<<"    ****  "<<"  **     "<<"     **** "<<endl;
}

void calculateRlRiseAndFall()
{
            //declaration and initialization of variables to use in the calculation of reduced
            //levels using the Rise and Fall method
            double benchmarkRL, previousRL, lastForesightRL = 0.0, sumOfRises = 0.0, sumOfFalls = 0.0;
            double sightValue, change, previousSightValue = 0.0;
            char sightType;
            double *reducedLevels;
            //Asks the user for the benchmark reduced level
            cout << "\nEnter the reduced level of the benchmark: ";
            cin >> benchmarkRL;//user enters the reduced level of the benchmark
            previousRL = benchmarkRL;//the benchmark reduced level equals to the first reduced level
            int numberOfReadings;
            cout << "Enter the number of readings: ";//enter the number of readings with backsight and foresight
            //being different readings
            cin >> numberOfReadings;//The user enters the number of readings he/she has recorded

            //creating an array called reducedlevels and keyword new is used to dynamically
            //allocate memory for an array of double values and the size of the array is determined
            //by the variable numberOfReadings
            reducedLevels = new double[numberOfReadings];

            for (int i = 0; i < numberOfReadings; i++)
            {
                //Displays a message to the user to enter the reading type whether
                //backsight, intersight or foresight and also the reading for that sight
                cout << "Enter reading type (B=backsight, F=foresight, I=intersight) and value for point " << i + 1 << ": ";
                cin >> sightType >> sightValue;//user enters sight type and the reading
                
                //if the entered reading is a backsight
                if (sightType == 'B')
                {
                    if (i == 0) // First backsight
                    {
                        //First reduced level is equal to benchmark reduced level
                        reducedLevels[i] = benchmarkRL;
                    }
                    else // Subsequent backsights
                    {
                        //reduced level of the backsight = reduced level of the foresight of
                        //the previous instrument station 
                        reducedLevels[i] = lastForesightRL;
                    }
                    previousRL = reducedLevels[i];
                }
                else//if the reading is a foresight or an intersight
                {
                    //change in readings declaration
                    double change = previousSightValue - sightValue;
                    if (change > 0)//if it is a positive change
                    {
                        //adds it to the total of rises
                        sumOfRises += change;
                    }
                    else//if change is negative
                    {
                        //adds it to the sum of falls
                        sumOfFalls -= change; // change is negative, so subtract to add the absolute value
                    }
                    previousRL += change;
                    reducedLevels[i] = previousRL;

                    if (sightType == 'F')
                    {
                        lastForesightRL = previousRL;
                    }
                }
                previousRL += (sightType == 'F') ? -change : change;
                reducedLevels[i] = previousRL;
                previousSightValue = sightValue;
            }

            cout<<"\n";
            // Output the table heading for outputing the results
            cout << left << setw(10) << "Point" << setw(15) << "Reduced Level(m)" << endl;

            // Output the reduced levels for all the points
            for (int i = 0; i < numberOfReadings; ++i)
            {
            cout << left << setw(10) << i + 1 << setw(15) << reducedLevels[i] << endl;
            }

            // Perform an arithmetic check for the reduced levels, sum of rises and falls
            cout << "Arithmetic Check: Sum of Rises - Sum of Falls = " << sumOfRises - sumOfFalls << "m" << endl;
            cout << "Should equal Last RL - First RL: " << reducedLevels[numberOfReadings - 1] - benchmarkRL << "m" << endl;

            // Deallocate memory to prevent memory leaks
            delete[] reducedLevels;
}

void calculateRlHOC()
{//declaration of the variables to use in the calculations
            int numberOfReadings;
            double benchmarkRl, sight, hoc, rl;
            char sightType;
            bool firstBacksight = true;
            double lastForesightRL;

            //Asks the user for the benchmark's reduced level
            cout << "\nEnter the benchmark reduced level: ";
            cin >> benchmarkRl;//user inputs the reduced level
            cout << "Enter the number of readings: ";//asks for the number of readings taken for all station positions
            cin >> numberOfReadings;//user enters the number of readings

            // Define a struct to hold the reading information
            struct Reading 
            {
                //declaration of the information the struct will hold
                int point;
                char sightType;//whether backsight, intersight or foresight
                double sight;//the reading of the sight
                double rl;
            };

            // Create an array to store the readings
            Reading readings[100]; // Assuming there won't be more than 100 readings to be taken

            for(int i = 0; i < numberOfReadings; i++)
            {
                cout << "Enter reading for point " << i+1 << " (B for backsight, F for foresight, I for intersight): ";
                cin >> sightType >> sight;

                if (sightType == 'B')//if it's a backsight reading entered
                {
                    if (firstBacksight)//if it's  the first backsight being entered
                    {
                        hoc = calculateHOC(benchmarkRl, sight);//calculated from function(calculateHOC)
                        rl = benchmarkRl;//Reduced level for the first backsight is reduced level of benchmark
                        firstBacksight = false;
                    }
                    else
                    {
                        hoc = lastForesightRL + sight;
                        rl = lastForesightRL;
                    }
                }
                else
                {
                    rl = calculateRL(hoc, sight, false);
                    if (sightType == 'F')
                    {
                    lastForesightRL = rl;
                    }
                }

                // Store the reading information
                readings[i] = {i+1, sightType, sight, rl};
            }

            // Print the heading of the table
            cout << left << setw(10) << "Point" << setw(10) << "Type" << setw(15) << "Sight" << setw(15) << "RL(m)" << endl;

            // Print all readings in tabular form with point number, sight type, sight and reduced levels
            
            for(int i = 0; i < numberOfReadings; ++i) 
            {
                cout << left << setw(10) << readings[i].point
                << setw(10) << readings[i].sightType
                << setw(15) << readings[i].sight
                << setw(15) << fixed << setprecision(3) << readings[i].rl << endl;
            }

}

void errorMessage()
{
    cout <<"Invalid option for calculating reduced levels. Please choose 1 or 2."<<endl;
}

/**
 * The main function is the entry point of the program.
 * It calculates the reduced levels based on the user's choice of method.
 * The user can choose between the Rise and Fall Method (option 1) or the Height of Collimation Method (option 2).
 * The function prompts the user for the necessary inputs and performs the calculations accordingly.
 * It also displays the calculated reduced levels in a table format.
 * 
 * Return: 0 indicating successful execution of the program.
 */
int main()
{
        //This displays the name of the group (GROUP 9) as the heading of the program
        groupName();
        //Declaration of variables for number of points(numPoints), reduced level option(rlOption),
        //benchmark reduced levels (benchmarkRl) and backsight reading(bs)
        int numPoints,rlOption;
        double benchmarkRl, bs;
        //Displays the option to select the method for calculating the reduced levels either using height of collimation
        //or Rise and Fall method
        cout<<"\n\nCALCULATING REDUCED LEVELS"<<endl;
        cout<<"\nChoose a method for calculating reduced levels: "<<endl;
        cout<<"1. Rise and Fall Method"<<endl;
        cout<<"2. Height of Collimation Method"<<endl;
        cout<<"Enter your choice (1 or 2): ";
        cin>>rlOption;//The user enters the reduced level option he wishes to use in the calculation


        //if the user chooses option 1 (rise and fall method)
        if (rlOption == 1)
        {
            calculateRlRiseAndFall();
        }


        else if (rlOption == 2)//if user wishes to use the height of collimation method
        {
            calculateRlHOC();
        }

        else//if it's not option 1 or 2
        {
            errorMessage();
        }


    return 0;//the return value for the main function

}
