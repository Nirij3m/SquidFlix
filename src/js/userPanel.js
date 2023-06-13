// ------- WRITE FILE -------
function writeFile(counter, id_form,func, destionnation) {

    //console.log("Poulpe");

    var element = document.createElement('a'); //creation d'une balise <a>
    let save = ""; //Texte à mettre dans le fichier
    //console.log(save);
    //console.log("element : " + element);

    for(let j = 0; j < counter ; j ++){ //Boucle si multifiltre pour faire toutes les demande

        //console.log("id_form : " + id_form[j]);

        let text1 = document.getElementById(id_form[j]).value; //octenir les valeurs dans le form
        //console.log("text : " + text1);

        let count = text1.length; //taille
        //console.log("count : " + count);

        //console.log(func[j]);
        let textToSave = destionnation + ";" + func[j] + ";";
        //console.log(textToSave);

        for(let i = 0;i<=count-1;i++){ //ecriture
            textToSave += text1[i];
            //console.log("TextToSave_1 : " + textToSave);
            //console.log("text1[i] : " + text1[i]);
        }

        save += textToSave + "\n" //retour à la ligne
        //console.log(save);
    }

    //console.log(save);

    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(save));
    element.setAttribute('download', 'request.txt');

    element.style.display = 'none';
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);

    // text1.submit();
}
// ------- WRITE FILE -------



function addFilm() {
    document.getElementById("addMember").addEventListener("click", function () {
        //Création des éléments essentiels
        let container = document.createElement("div");
        container.className = "tempCard";
        let target = document.getElementById("target");
        let checkButton = document.createElement("i")
        checkButton.className = "fa-solid fa-check";
        checkButton.id = "checkButton";
        checkButton.style.color = "#ffb100";

        let deleteButton = document.createElement("i");
        deleteButton.className = "fa-solid fa-trash deleteButton";
        deleteButton.style.color = "#540404";


        //création de toutes les inputs
        let inputName = document.createElement("input");
        inputName.setAttribute("type", "text");
        inputName.setAttribute("placeholder", "Réalisateur");
        inputName.className = "inputCard"

        let inputProject = document.createElement("input");
        inputProject.setAttribute("type", "text");
        inputProject.setAttribute("placeholder", "Titre");
        inputProject.className = "inputCard"

        let inputSite = document.createElement("input");
        inputSite.setAttribute("type", "text");
        inputSite.setAttribute("placeholder", "Genre");
        inputSite.className = "inputCard"

        let inputEmail = document.createElement("input");
        inputEmail.setAttribute("type", "text");
        inputEmail.setAttribute("placeholder", "Duration");
        inputEmail.className = "inputCard"



        let span = document.createElement("span");
        span.className = "buttonContainer";
        span.appendChild(checkButton);
        span.appendChild(deleteButton);

        //Ajout des inputs dans le container
        container.appendChild(inputName);
        container.appendChild(inputProject);
        container.appendChild(inputSite);
        container.appendChild(inputEmail);
        container.appendChild(span);


        //Ajout du container dans la cible
        target.appendChild(container);

        updateDeleteButton(); //Mets à jour le listner pour les boutons de suppression
        let sender = document.getElementsByTagName("form")[0];
        //Si jamais on valide l'entrée
        checkButton.addEventListener("click", function() {


            let finalResult = inputName.value + " " + inputProject.value + " " + inputSite.value + " " + inputEmail.value;
            document.getElementsByTagName("form")[0].children[0].value = finalResult;
            console.log(finalResult);

            writeFile(1,['sendIt'],["addFilm"], "P");
            this.parentNode.parentNode.remove();
        });

    });
}

function updateDeleteButton() {
    let deleteButtons = document.querySelectorAll(".deleteButton");
    for (let i = 0; i < deleteButtons.length; i++) {
        deleteButtons[i].addEventListener("click", function() {
            this.parentNode.parentNode.remove();
        });
    }
}

function main(){
    addFilm();
}
main();