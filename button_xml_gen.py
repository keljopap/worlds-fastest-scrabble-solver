def print_button(x, y):
    print "<Button"
    if (x!=0 or y!=0):
        print "\tandroid:layout_width=\"match_parent\""
        print "\tandroid:layout_height=\"match_parent\""
    else:
        print "\tandroid:layout_width=\"1px\""
        print "\tandroid:layout_height=\"1px\""
    print "\tandroid:layout_gravity=\"fill\""
    print "\tandroid:layout_row=\""+str(x)+"\""
    print "\tandroid:layout_column=\""+str(y)+"\""
    print "\tandroid:text=\"("+str(x)+","+str(y)+")\" />\n"

def main():

    for i in range(4):
        for j in range(4):
            print_button(i, j)

if __name__ == "__main__":
    main()
