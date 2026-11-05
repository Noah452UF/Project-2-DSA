
const parameters = [-1,-1,-1,-1,-1,-1,-1];
const loadnum=10;


//update array depending on which button is pushed and where in the array to insert
function dropdowntoarray(parameter, num){
    parameters[num]=parameter;
    
    //console.log("Clicked: ", num, parameters[num]);
}


//update array based on whats entered into the field



function arraytojson(){
    //should be neagtive 1 if theres no parameters

    parameters[2]=document.getElementById("gm1").value;
    parameters[3]=document.getElementById("gm2").value;
    parameters[4]=document.getElementById("hp1").value;
    parameters[5]=document.getElementById("hp2").value;

    for(const i in parameters){
        console.log(parameters[i]);
    }
}





//if final button add the whole array to the json, and then run the c++ code...somehow.