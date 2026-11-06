let parameters = [-1,-1,-1,-1,-1,-1,-1,-1];
const loadnum=10;
let inputJSON = {};

//maybe let them input number of entries since its dynamic anyways?

//gets data for the table
async function gettabledata(){
    const towrite= document.getElementById("carrow");
    const val=2;

    const wholejson= await fetch("cars.json");
    const cars=await wholejson.json();

    for(let i=0;i<10;i++){
        //cars["Identification"]["Classification"]
        const car= `<tr>
            <th>${cars[i]["Identification"]["ID"]}</th>
            <th>${cars[i]["Engine Information"]["Engine Statistics"]["Horsepower"]}</th>
            <th>${val}</th>
        </tr>`;
        towrite.innerHTML+=car;
    }


}






//update array depending on which button is pushed and where in the array to insert
function dropdowntoarray(parameter, num){
    parameters[num]=parameter;
    console.log("Clicked: ", num, parameters[num]);
}


//update array based on whats entered into the field
async function arraytojson(){
    console.log("ArraytoJSON");
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

