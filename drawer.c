#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
 ! Normal Graph
 *
 *
 *
 *
 */

/*
 ! Binary Tree
 * Generally, the drawing of the graphs will be in this format
 *
 *               ╔═══════════╗
 *               ║<Node Data>║
 *               ╚═══════════╝
 *           ┌─────────┴─────────┐
 *     ╔═══════════╗       ╔═══════════╗
 *     ║<Node Data>║       ║<Node Data>║
 *     ╚═══════════╝       ╚═══════════╝
 *  ┌────────┴────────┐ ┌────────┴────────┐
 *  ╧                 ╧ ╧                 ╧
 *  Notes:
 *  1.) <Node Data> width should be odd length
 *  2.) Maximum width should be calculated first before drawing the graph for spacing determination
 *  3.) Width per box is: 2 + <Node Data> length
 *  4.) Minimum spacing between nodes is 7. Excludes null nodes
 *
 *  General algorithm:
 *  1.) Root node: Get spacing required for root node, print root node
 *
 */
void printBinaryTree()
{
}

void printNode(char *data)
{
    int width = strlen(data);
    bool isEven = width % 2 == 0;
    if (isEven)
        width++; // ensure odd

    // print top
    printf("╔");
    repeatPrint('═', width);
    printf("╗\n");

    // print data
    printf("║%s", data);
    if (isEven)
        printf(" "); // add filler if necessary
    printf("║\n");

    // print bottom
    printf("╚");
    repeatPrint('═', width);
    printf("╝\n");
}

void repeatPrint(char c, int n)
{
    for (int i = 0; i < n; i++)
        printf("%c", c);
}