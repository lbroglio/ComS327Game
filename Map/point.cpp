Point::Point(int row, int col){
    this->rowNum = row;
    this->colNum = col;
}

int Point::getID(){
    if(rowNum == 0 ||rowNum == 20 || colNum == 0 ||colNum == 79){
        return -1;
    }

    int id = convertPoint();

    //Reindex the ID
    int rowLoc =  id / 80;
    return id - (81 + ((rowLoc -1) * 2));
}


Point convertID(int toConvert){
    Point converted;
    converted.rowNum = toConvert / 80;
    converted.colNum = toConvert % 80;

   return converted;
}

Point::Point(){
    this->rowNum = 0;
    this->colNum = 0;
}


Point* Point::clone(){
    //Can't use malloc here. Use new and delete to run constructors and destructors
    Point* temp = new Point(this->rowNum,this->colNum);
    return temp;
}