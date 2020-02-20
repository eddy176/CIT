// vue javascript

var createMeal = function (meal) {
    var data = `meat=${encodeURIComponent(meal.meat)}`;
    data += `&veggie=${encodeURIComponent(meal.veggie)}`;
    data += `&side=${encodeURIComponent(meal.side)}`;

    return fetch("http://localhost:8080/meals", {
       method: "POST",
       headers: {
           "Content-type": "application/x-www-form-urlencoded"
       },
       body: data
    });
};

var getMeals = function () {
    return fetch('http://localhost:8080/meals');
};


var app = new Vue({
    el: '#app',
    data: {
        showMealForm: false,
        meat: '',
        veggie: '',
        side: '',
        meals: []
    },
    methods: {
        addMeal: function () {
            createMeal ({
                meat: this.meat,
                veggie: this.veggie,
                side: this.side
            }).then(response => {
                // handle server response
                // reload vehicle data
                console.log("Vehicle created.");
                this.refreshMeals();
            });

            this.meat = '';
            this.veggie = '';
            this.side = '';
            this.showMealForm = false;
        },
        newMeal: function () {
            this.showMealForm = true;
        },
        refreshMeals: function () {
            getMeals().then(response => {
                response.json().then(data => {
                    this.meals = data;
                });
            });
        }
    },
    created: function()  {
        console.log("Vue.js is ready");
        this.refreshMeals();
    }
});
