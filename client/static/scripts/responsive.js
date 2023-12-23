let menuicn = document.querySelector(".menuicn"); 
let closemenuicn = document.querySelector(".closemenuicn"); 
let nav = document.querySelector(".navcontainer"); 


let navOptions = document.querySelectorAll(".option1, .option2, .option3, .option4, .option5, .option6");

navOptions.forEach(option => {
    option.addEventListener("click", function() {
      // Remove the "selected" class from all options
      navOptions.forEach(otherOption => {
        otherOption.style.backgroundColor = "#fafaff";
        otherOption.style.color = "#3f3939";
        otherOption.style.borderLeft = "";
        // otherOption.classList.remove("selected");
      });

      // Add the "selected" class to the clicked option
      option.style.backgroundColor = "#c3c1c5";
      option.style.color = "#e7e5e5";
      option.style.borderLeft  =  "5px solid #a2a2a2";
    //   option.classList.add("selected");
    });
  });


menuicn.addEventListener("click", () => { 
    menuicn.style.display ='none';
    closemenuicn.style.display = 'block';
	nav.classList.toggle("navclose"); 
})

closemenuicn.addEventListener("click", () => { 
    menuicn.style.display ='block';
    closemenuicn.style.display = 'none';
	nav.classList.toggle("navclose"); 
})


// if (selectedTick.style.display === 'block') {
//     // If the selected tick is already visible, hide it (toggle off)
//     selectedTick.style.display = 'none';
//     // Optionally, you may want to reset or clear the selected avatar ID here
//     console.log(`Deselected Avatar: ${avatarId}`);
// } else {
//     // Reset all ticks
//     const allTicks = document.querySelectorAll('.tick');
//     allTicks.forEach(tick => tick.style.display = 'none');

//     // Show the tick for the selected avatar
//     selectedTick.style.display = 'block';

//     avatar = avatarId;
//     // Store the selected avatar ID or perform any other necessary actions
//     console.log(`Selected Avatar: ${avatarId}`);
// }
