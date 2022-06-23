
#include <iostream>
#include <string.h>
#include <io.h>
#include <string>
using namespace std;
string unixTimeToHumanReadable(long int seconds)
{

    // Save the time in Human
    // readable format
    string ans = "";

    // Number of days in month
    // in normal year
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };

    long int currYear, daysTillNow, extraTime,
        extraDays, index, date, month, hours,
        minutes, secondss, flag = 0;

    // Calculate total days unix time T
    daysTillNow = seconds / (24 * 60 * 60);
    extraTime = seconds % (24 * 60 * 60);
    currYear = 1970;

    // Calculating current year
    while (daysTillNow >= 365) {
        if (currYear % 400 == 0
            || (currYear % 4 == 0
                && currYear % 100 != 0)) {
            daysTillNow -= 366;
        }
        else {
            daysTillNow -= 365;
        }
        currYear += 1;
    }

    // Updating extradays because it
    // will give days till previous day
    // and we have include current day
    extraDays = daysTillNow + 1;

    if (currYear % 400 == 0
        || (currYear % 4 == 0
            && currYear % 100 != 0))
        flag = 1;

    // Calculating MONTH and DATE
    month = 0, index = 0;
    if (flag == 1) {
        while (true) {

            if (index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }
            else {
                if (extraDays
                    - daysOfMonth[index]
                    < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else {
        while (true) {

            if (extraDays
                - daysOfMonth[index]
                < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
        }
    }

    // Current Month
    if (extraDays > 0) {
        month += 1;
        date = extraDays;
    }
    else {
        if (month == 2 && flag == 1)
            date = 29;
        else {
            date = daysOfMonth[month - 1];
        }

    }
    
    // Calculating HH:MM:YYYY
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    secondss = (extraTime % 3600) % 60;

    ans += to_string(date);
    ans += ".";
    month > 10 ? ans += to_string(month) : ans += to_string(0) + to_string(month);
    ans += ".";
    ans += to_string(currYear);
    ans += " ";
    ans += to_string(hours);
    ans += ":";
    ans += to_string(minutes);
    ans += ":";
    ans += to_string(secondss);

    // Return the time
    return ans;
}
int main()
{
    srand(time(NULL));
    const char* path = "b_data.dat";
    int n = 10, imax, imin;
    int i;
    int* a, max, min;
    int* b;
    int c;
    FILE* f;
    if (fopen_s(&f, path, "wb") != NULL) cout << "The file cannot be opened";
    else
    {
        int fx;
        for (int i =0; i < n; i++)
        {
            fx = i + 10;
            fwrite(&fx, sizeof(int), 1, f);
        }
        fclose(f);
    }
    if (fopen_s(&f, path, "rb") != NULL) cout << "The file cannot be opened";
    else
    {
        a = new int[n];
        fread(a, sizeof(int), n, f);
        for (int i = 0; i < n; i++)
            cout <<a[i] <<"\t";
        cout << '\n';
        for (imax = imin = 0, max = min = a[0], i = 1; i < n; i++)
        {
            if (a[i] > max)
            {
                max = a[i];
                imax = i;
            }
            if (a[i] < min)
            {
                min = a[i];
                imin = i;
            }
        }
    }
    cout <<"min " << min <<" imin " << imin <<" max " << max <<" imax "<<imax << endl;
    fclose(f);
    if (fopen_s(&f, path, "rb+") != NULL) cout << "The file cannot be opened";
    else
    {
        fseek(f, (imin + 0) * sizeof(int), SEEK_SET);
     //   cout << ftell(f) <<endl;
        fwrite(&max, sizeof(int), 1, f);
     //   cout << ftell(f)<<endl;
        fseek(f, (imax +0) * sizeof(int), SEEK_SET);
     //   cout << ftell(f) << endl;
        fwrite(&min, sizeof(int), 1, f);
     //   cout << ftell(f) << endl;
    }
           fclose(f);
        b = new int[n];
        if (fopen_s(&f, path, "rb") != NULL) cout << "The file cannot be opened";
        else
        {
            for (int i = 0; i<n; i++)
            fread(&b[i], sizeof(int), 1, f);
        }
        fclose(f);
        for (int i = 0; i < n; i++) {

            cout << b[i] << "\t";
        }

        struct _finddata_t myfileinfo;

        long done = _findfirst("*.cpp", &myfileinfo);

        cout <<"\n" << unixTimeToHumanReadable(myfileinfo.time_create);

        return 0;
    return 0;
}

