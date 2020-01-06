var novemberizing = {
    chart: {
        init: function(){
            console.log("hello");
            Chart.plugins.register({
                afterDatasetsDraw: function(chart) {
                    var ctx = chart.ctx;

                    chart.data.datasets.forEach(function(dataset, i) {
                        var meta = chart.getDatasetMeta(i);
                        if (!meta.hidden) {
                            meta.data.forEach(function(element, index) {
                                // Draw the text in black, with the specified font
                                ctx.fillStyle = 'rgb(0, 0, 0)';

                                var fontSize = 16;
                                var fontStyle = 'normal';
                                var fontFamily = 'Helvetica Neue';
                                ctx.font = Chart.helpers.fontString(fontSize, fontStyle, fontFamily);

                                // Just naively convert to string for now
                                var dataString = dataset.data[index].v;

                                // Make sure alignment settings are correct
                                ctx.textAlign = 'center';
                                ctx.textBaseline = 'middle';

                                var padding = 5;
                                var position = element.tooltipPosition();
                                ctx.fillText(dataString, position.x, position.y - (fontSize / 2) - padding);
                            });
                        }
                    });
                }
            });
        }
    },
    tree: {
        show: function(s, type, parent, depth, horizontal){
            if(type === 'binary search tree'){
                var div = document.createElement("div");
                var canvas = document.createElement('canvas');
                div.style.width = "800px";
                div.style.height = "400px";
                div.appendChild(canvas);
                var context = canvas.getContext('2d');
                var data = {
                    datasets: [{
                        label: "node",
                        radius: 3,
                        borderColor: '#000000',
                        backgroundColor: '#000000',
                        data: JSON.parse(s)
                    }]
                };
                if(parent !== undefined){
                    var o = document.getElementById(parent);
                    o.appendChild(div);
                } else {
                    document.body.appendChild(div);
                }
                new Chart(context, {
                    type: 'scatter',
                    data: data,
                    options: {
                        // responsive: true,
                        // maintainAspectRatio: false,
                        tooltips: {
                            callbacks: {
                                label: function(tooltipItem, data) {
                                    return data.datasets[tooltipItem.datasetIndex].data[tooltipItem.index].v;
                                }
                            }
                        },
                        legend: {
                            display: false
                        }
                    }
                });
            } else {
                console.log("not support");
            }
        }
    }
};
