class Menu {
 private:
  Swordf *sf;
  
 public:
  Menu(Swordf *isf){
    sf = isf;
  }

  void show(){
    sf->togglePause();
    //display menu
    //set input methods
  }
};
