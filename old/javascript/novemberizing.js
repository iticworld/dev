var novemberizing = {
    chart: {
        init: function(){
            console.log("hello");
            Chart.plugins.register({
                afterDatasetsDraw: function(chart) {
                    let ctx = chart.ctx;

                    chart.data.datasets.forEach(function(dataset, i) {
                        let meta = chart.getDatasetMeta(i);
                        if (!meta.hidden) {
                            meta.data.forEach(function(element, index) {
                                // Draw the text in black, with the specified font
                                ctx.fillStyle = 'rgb(0, 0, 0)';

                                let fontSize = 16;
                                let fontStyle = 'normal';
                                let fontFamily = 'Helvetica Neue';
                                ctx.font = Chart.helpers.fontString(fontSize, fontStyle, fontFamily);

                                // Just naively convert to string for now
                                // var dataString = (dataset[i].data[index].c === 1 ? "R("+dataset[i].data[index].v + ")" : "B("+dataset[i].data[index].v + ")");
                                let dataString = dataset.data[index].v;

                                // Make sure alignment settings are correct
                                ctx.textAlign = 'center';
                                ctx.textBaseline = 'middle';

                                let padding = 5;
                                let position = element.tooltipPosition();
                                ctx.fillText(dataString, position.x, position.y - (fontSize / 2) - padding);
                            });
                        }
                    });
                }
            });
        }
    },
    tree: {
        show: function(s, type, parent, vertical, horizontal){
            if(type === 'binary search tree'){
                let div = document.createElement("div");
                let canvas = document.createElement('canvas');
                div.style.width = "800px";
                div.style.height = "400px";
                div.appendChild(canvas);
                let context = canvas.getContext('2d');
                let param = JSON.parse(s);
                let data = {
                    datasets: [{
                        label: "node",
                        radius: 3,
                        borderColor: '#000000',
                        backgroundColor: '#000000',
                        data: Array.isArray(param) ? param : param.v
                    }]
                };
                console.log(data.datasets.data);
                console.log(param);
                if(parent !== undefined){
                    let o = document.getElementById(parent);
                    o.appendChild(div);
                } else {
                    document.body.appendChild(div);
                }
                let options =  {
                    responsive: true,
                    maintainAspectRatio: false,
                    tooltips: {
                        callbacks: {
                            label: function(tooltipItem, data) {
                                return data.datasets[tooltipItem.datasetIndex].data[tooltipItem.index].v;
                            }
                        }
                    },
                    legend: {
                        display: true
                    },
                    scales: {
                        yAxes: [{
                            ticks: {
                                beginAtZero: true
                            }
                        }],
                        xAxes: [{
                            ticks: {
                                beginAtZero: true
                            }
                        }]
                    }
                };
                if(vertical !== undefined) {
                    options.scales.yAxes[0].ticks.min = 0;
                    options.scales.yAxes[0].ticks.max = vertical + 1;
                } else if(param.vertical !== undefined){
                    options.scales.yAxes[0].ticks.min = 0;
                    options.scales.yAxes[0].ticks.max = param.vertical + 1;
                }

                if(horizontal !== undefined){
                    options.scales.xAxes[0].ticks.min = 0;
                    options.scales.xAxes[0].ticks.max = horizontal;
                } else if(param.horizontal !== undefined) {
                    options.scales.xAxes[0].ticks.min = 0;
                    options.scales.xAxes[0].ticks.max = param.horizontal;
                }
                new Chart(context, {
                    type: 'scatter',
                    data: data,
                    options: options
                });
            } else if(type === 'red black tree'){
                let json = JSON.parse(s);
                let div = document.createElement("div");
                let canvas = document.createElement('canvas');
                div.style.width = "800px";
                div.style.height = "400px";
                div.appendChild(canvas);
                let context = canvas.getContext('2d');
                let data = {
                    datasets: [{
                        label: "RED",
                        radius: 3,
                        borderColor: '#FF0000',
                        backgroundColor: '#FF0000',
                        data: Array.isArray(json) ? json[0] : json.r
                    }, {
                        label: "BLACK",
                        radius: 3,
                        borderColor: '#000000',
                        backgroundColor: '#000000',
                        data: Array.isArray(json) ? json[1] : json.b
                    }]
                };
                if(parent !== undefined){
                    const o = document.getElementById(parent);
                    o.appendChild(div);
                } else {
                    document.body.appendChild(div);
                }
                let options =  {
                    responsive: true,
                    maintainAspectRatio: false,
                    tooltips: {
                        callbacks: {
                            label: function(tooltipItem, data) {
                                return data.datasets[tooltipItem.datasetIndex].data[tooltipItem.index].v;
                            }
                        }
                    },
                    legend: {
                        display: false,
                        position: 'left'
                    },
                    scales: {
                        yAxes: [{
                            ticks: {
                                display: false,
                                beginAtZero: true
                            }
                        }],
                        xAxes: [{
                            ticks: {
                                display: false,
                                beginAtZero: true
                            }
                        }],
                    }
                };
                if(vertical !== undefined) {
                    options.scales.yAxes[0].ticks.min = 0;
                    options.scales.yAxes[0].ticks.max = vertical + 1;
                } else if(json.vertical !== undefined){
                    options.scales.yAxes[0].ticks.min = 0;
                    options.scales.yAxes[0].ticks.max = json.vertical + 1;
                }

                if(horizontal !== undefined){
                    options.scales.xAxes[0].ticks.min = 0;
                    options.scales.xAxes[0].ticks.max = horizontal;
                } else if(json.horizontal !== undefined) {
                    options.scales.xAxes[0].ticks.min = 0;
                    options.scales.xAxes[0].ticks.max = json.horizontal;
                }
                new Chart(context, {
                    type: 'scatter',
                    data: data,
                    options: options
                });
            } else {
                console.log("not support");
            }
        }
    },
    html: {
        add: function(s, parent, tag){
            let div = document.createElement(tag !== undefined ? tag : 'div');
            div.appendChild(document.createTextNode(s));
            if(parent !== undefined){
                let o = document.getElementById(parent);
                o.appendChild(div);
            } else {
                document.body.appendChild(div);
            }
            return div;
        }
    }
};