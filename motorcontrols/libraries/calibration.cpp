#include "calibration.hpp"

void calibrateLocations(const char* location_file_path) {
    short complete = 0;
    char input;
    char trash[256];
    
    loadLocations(location_file_path);
    printMenu();
    
    while (!complete) {
        printf("Type a command:\n");
        input = getchar();
        input = tolower(input);
        fgets(trash, sizeof(trash), stdin);
        
        complete = processInput(input, location_file_path);
    }
}

void printMenu() {
    printf("--- MENU ---\n'c' capture current position\n'p' print locations\n's' save locations\n'r' remove a location\n'q' quit the program\n\n");
}

short processInput(char i, const char* location_file_path) {
    switch (i) {
        case 'q':
            return 1;
        case 'm':
            printMenu();
            break;
        case 'c':
            captureLocation();
            break;
        case 'p':
            printLocations();
            break;
        case 's':
            saveLocations(location_file_path);
            break;
        case 'r':
            removeLocation();
            break;
        default:
            printf("That is not a know command, enter 'M' for menu.\n\n");
    }
    
    return 0; // by default return not complete
}

void loadLocations(const char* location_file_path) {
    char in;
    int cnt = 0;
    std::string num;
    
    std::ifstream loc_file;
    loc_file.open(location_file_path);
    if (loc_file.is_open()) {
        // loop throug the location file
        while (loc_file >> in) {
            if (isdigit(in))
                num += in;
            else {
                if (cnt%2 == 0)
                    locations.push_back(std::vector<int>());
                
                locations[cnt/2].push_back(std::stoi(num));
                    
                num = "";
                cnt++;
            }
        }
        locations[cnt/2].push_back(std::stoi(num));
    }
    loc_file.close();
}

void saveLocations() {
    std::ofstream loc_file;
    loc_file.open(location_file_path);
    
    if (loc_file.is_open()) {
        for (int i = 0; i < locations.size(); i++) {
            loc_file << locations[i][0] << ',' << locations[i][1] << (i==locations.size()-1?"":",");
        }
    }
    
    loc_file.close();
    printf("save successful!\n\n");
}

void removeLocation() {
    int loc = -1;
    
    printLocations();
    printf("Which location would you like to remove?\n");
    
    while(loc < 0 || loc >= locations.size()) {
        std::cin >> loc;
        std::cin.get();
        loc--;
    }
    
    locations.erase(locations.begin()+loc);
    printLocations();
}

void printLocations() {
    if (locations.size() == 0)
        printf("No locations captured.\n\n");
    else {
        printf("Locations:\n");
        for (int i=0; i < locations.size(); i++)
            printf("%d. %d, %d\n", i+1, locations[i][0], locations[i][1]);
        printf("\n");
    }
    
}

void captureLocation() {
    if (locations.size() > 4) {
        printf("You can only save up to 4 locations.\n\n");
        return;
    }

    locations.push_back(std::vector<int>());
    locations[locations.size()-1].push_back(ADC_Rd(0x83C5));
    locations[locations.size()-1].push_back(ADC_Rd(0x83D5));
}
