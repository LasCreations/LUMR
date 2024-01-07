

export function decoder(){
    if (window.location.href.includes('/secure/dashboard.html')){
        var data = JSON.parse(atob(decodeURIComponent(window.location.search.replace('?data=', ''))));
        console.log(data);  // Outputs: data from signup
    }
}