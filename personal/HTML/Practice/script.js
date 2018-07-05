var change = function(x) {
    switch(x.count){
        case 0: 
            x.className="redText";
            break;
        case 1:
            x.className="orangeText";
            break;
        case 2:
            x.className="yellowText";
            break;
        case 3:
            x.className="greenText";
            break;
        case 4:
            x.className="blueText";
            break;
        case 5:
            x.className="purpleText";
            break;
    }
}