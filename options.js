
let parameters = [-1,-1,-1,-1,-1,-1,-1,-1];
const loadnum=10;
let inputJSON = {};


//update array depending on which button is pushed and where in the array to insert
function dropdowntoarray(parameter, num){
    parameters[num]=parameter;
    console.log("Clicked: ", num, parameters[num]);
}


//update array based on whats entered into the field


async function arraytojson(){
    console.log("called");
    //should be neagtive 1 if theres no parameters
    parameters[2]=document.getElementById("gm1").value;
    parameters[3]=document.getElementById("gm2").value;
    parameters[4]=document.getElementById("hp1").value;
    parameters[5]=document.getElementById("hp2").value;

    for(const i in parameters){
        console.log(parameters[i]);
    }

    inputJSON["isB++"] = parameters[0];
    inputJSON["sortby"] = parameters[1];
    inputJSON["horsepow1"] = parameters[2];
    inputJSON["horsepow2"] = parameters[3];
    inputJSON["gasmileage1"] = parameters[4];
    inputJSON["gasmileage2"] = parameters[5];
    inputJSON["driveline"] = parameters[6];
    inputJSON["brand"] = parameters[7];

    //post request here
    const response= await fetch("http://localhost:3000/options",{
        method: "POST",
        body: JSON.stringify(inputJSON)
    });
    
        
    //runs the c++ code...somehow.
}

