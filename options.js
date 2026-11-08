let parameters = [-1,-1,-1,-1,-1,-1,-1,-1,-1];
const loadnum=10;
let inputJSON = {};

//gets data for the table
async function gettabledata(){
    const towrite= document.getElementById("carrow");
    const val=2;

    const wholejson= await fetch("results.json");
    const cars=await wholejson.json();
    towrite.innerHTML="";
    for(let i=0;i<cars.length-1;i++){
        //cars["Identification"]["Classification"]
        const car= `<tr>
            <th>${cars[i]["Identification"]["ID"]}</th>
            <th>${cars[i]["Engine Information"]["Engine Statistics"]["Horsepower"]}</th>
            <th>${val}</th>
        </tr>`;
        towrite.innerHTML+=car;
    }

    
    const timejson= await fetch("time.json");
    const time=await timejson.json();
    const timewrite= document.getElementById("time");
    timewrite.innerHTML=`${time["Time"]}`;
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
    parameters[2]=document.getElementById("y").value;
    parameters[3]=document.getElementById("hp1").value;
    parameters[4]=document.getElementById("hp2").value;
    parameters[5]=document.getElementById("gm1").value;
    parameters[6]=document.getElementById("gm2").value;

    for(const i in parameters){
        console.log(parameters[i]);
        if(parameters[i]==="")
            parameters[i]=-1;
        else
            parameters[i]=parseInt(parameters[i]);
    }

    inputJSON["isB++"] = parameters[0];
    inputJSON["sortby"] = parameters[1];
    inputJSON["year"] = parameters[2];
    inputJSON["horsepow1"] = parameters[3];
    inputJSON["horsepow2"] = parameters[4];
    inputJSON["gasmileage1"] = parameters[5];
    inputJSON["gasmileage2"] = parameters[6];
    inputJSON["driveline"] = parameters[7];
    inputJSON["Brand"] = parameters[8];



    //post request that writes the requirements to a json
    
    const response= await fetch("http://localhost:3000/options",{
        method: "POST",
        body: JSON.stringify(inputJSON)
    });
    console.log("requirements.json finished")

    //post request that runs the c++ code
    const exfile= await fetch("http://localhost:3000/execfile",{
        method: "POST",
    });

    console.log("c++ execution finished")

    gettabledata()
}

