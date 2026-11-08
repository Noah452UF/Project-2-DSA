
//used https://www.w3schools.com/nodejs/nodejs_http.asp
const fs=require('fs');
const http = require('http');
const { exec } = require('child_process')

//import cars from './cars.json' with {type:'json'};


//executes c++ code; should be called after the requirements are written and before table is made


const server = http.createServer((req,res) => {
    const{method, url}=req;

    //receiving the files to run
    if(method==="GET"){
        let name="." +url;
        if(url==="/")
            name="./index.html"
        //console.log("URL:", url);
        //console.log("Filename:", name);
        fs.readFile(name, (err, data)=>{
        if(err){
            console.log(err);
        }
        res.end(data);
    });
    return;
}
    //writing to the json
    if(method==="POST" && url==="/options"){
        let body="";
        console.log("wrote requirements.json")
        req.on("data", chunk =>{
            body+=chunk;
        });

        req.on("end",()=>{
            try{
                const inputJSON= JSON.parse(body);
                const towrite="requirements.json";
                fs.writeFile(towrite,JSON.stringify(inputJSON, null, 4),(err)=>{
                    return;
                });
                //console.log("Success")
            }
            catch(err){
                console.log(err);
            }
            res.end()
        });
    }
    //execute c++
    if(method==="POST" && url==="/execfile"){
        //compile
        exec('g++ -std=c++17 main.cpp cars.cpp -o cars.exe', (err)=>{
            if(err)
                console.log(err)
        });
        //run
        exec('cars.exe', (err)=>{
            if(err)
                console.log(err)
        });
        
        res.end()
}

});

//exec. c++ code here
server.listen(3000,'localhost', () => {
    console.log("http://localhost:3000");
});
