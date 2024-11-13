#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    FILE *fp, *outp;
    int i, addr1, l, j, staddr1;
    char name[10], name2[10], len[10], line[1000], name1[10], addr[10], rec[10], ch, staddr[10];
    fp = fopen("inp.txt", "r");
    outp = fopen("output.txt", "w");
    fscanf(fp, "%s", line);
    int count = 0, a = 0, b = 0, c = 0;
    for (i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == '^')
        {
            count++;
            continue;
        }
        if (count == 1)
            name1[a++] = line[i];
        else if (count == 2)
            name2[b++] = line[i];
        else if (count == 3)
            len[c++] = line[i];
    }

    name1[a] = '\0';name2[b] = '\0';len[c] = '\0';
    fprintf(outp, "Program Name : %s\n", name1);
    fprintf(outp, "Starting Address : %s\n", name2);
    do
    {
        fscanf(fp, "%s", line);
        if (line[0] == 'T')
        {
            count = 0;a = 0;
            for (i = 0; line[i] != '\0'; i++)
            {
                if (line[i] == '^')
                {
                    count++;
                    continue;
                }
                if (count == 1)
                    staddr[a++] = line[i];
                else if (count == 3)break;
            }
            staddr[a] = '\0';
            staddr1 = strtol(staddr, NULL, 16);
            i = 12;
            while (line[i] != '\0')
            {
                if (line[i] != '^')
                {
                    int objc1 = line[i];
                    int objc2 = line[i + 1];
                    objc1 -= 48;
                    if (objc1 > 10)
                        objc1 -= 7;
                    objc2 -= 48;
                    if (objc2 > 10)
                        objc2 -= 7;
                    int objc = objc1 * 16 + objc2;
                    fprintf(outp, "00%X  <----  %02X\n", staddr1, objc);
                    staddr1++;
                    i = i + 2;
                }
                else
                    i++;
            }
        }
        else if (line[0] = 'E')break;
    } while (!feof(fp));
    printf("program executed successfuly\n");
    fclose(fp);
    fclose(outp);
}


