use std::collections::HashMap;
use std::hash::Hash;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
enum SensorMetric {
    Load,
    Frequency,
    Temperature,
}

struct Event {
    timestamp: u64,
    sensor: String,
    metric: SensorMetric,
    value: f64,
}

fn group_and_aggregate<O, E, D, K>(
    events: &[E],
    group_fn: impl Fn(&E) -> K,
    data_fn: impl Fn(&E) -> Option<D>,
    aggregate: impl Fn(&[D]) -> O,
) -> HashMap<K, O>
where
    K: Eq + Hash, {
    
    let mut groups: HashMap<K, Vec<D>> = HashMap::new();

    for e in events {
        if let Some(data) = data_fn(e) {
            let key = group_fn(e);
            groups.entry(key).or_insert_with(Vec::new).push(data);
        }
    }

    groups.into_iter().map(|(key, data)| (key, aggregate(&data))).collect()
}

trait Aggregator {
    type Output;

    fn name(&self) -> String;
    fn aggregate(&self, events: &[Event]) -> Vec<(String, Self::Output)>;
}

struct TotalAggregator {}

impl Aggregator for TotalAggregator {
    type Output = f64;

    fn name(&self) -> String {
        "total".to_string()
    }

    fn aggregate(&self, events: &[Event]) -> Vec<(String, f64)> {
        let res = group_and_aggregate(
            events,
            |event| event.metric,
            |event| Some(event.value),
            |values| {
                if values.is_empty() {
                    0.0
                }
                else {
                    values.iter().sum::<f64>() / values.len() as f64
                }
            },
        );

        res.into_iter().map(|(metric, avg)| (format!("{:?}", metric), avg)).collect()
    }
}

struct MetricAggregator {
    metric: SensorMetric
}

impl Aggregator for MetricAggregator {
    type Output = f64;

    fn name(&self) -> String {
        format!("{:?}", self.metric)
    }

    fn aggregate(&self, events: &[Event]) -> Vec<(String, f64)> {
        let filtered_events: Vec<&Event> = events
            .iter()
            .filter(|event| event.metric == self.metric)
            .collect();

        let res = group_and_aggregate(
            &filtered_events,
            |event| event.sensor.clone(),
            |event| Some(event.value),
            |values| values.iter().sum::<f64>(),
        );

        res.into_iter().collect()
    }
}


fn main() {
    let all: Vec<Box<dyn Aggregator<Output=f64>>> = vec![
        Box::new(TotalAggregator{}),
        Box::new(MetricAggregator{metric: SensorMetric::Load}),
        Box::new(MetricAggregator{metric: SensorMetric::Temperature}),
    ];

    let events = &[
        Event { timestamp: 0, sensor: String::from("cpu0"), metric: SensorMetric::Load, value: 0.98 },
        Event { timestamp: 0, sensor: String::from("cpu1"), metric: SensorMetric::Load, value: 0.04 },
        Event { timestamp: 0, sensor: String::from("gpu0"), metric: SensorMetric::Load, value: 13.45 },
        Event { timestamp: 0, sensor: String::from("cpu0"), metric: SensorMetric::Frequency, value: 3100.00 },
        Event { timestamp: 0, sensor: String::from("cpu1"), metric: SensorMetric::Frequency, value: 3100.00 },
        Event { timestamp: 0, sensor: String::from("gpu0"), metric: SensorMetric::Frequency, value: 300.00 },
        Event { timestamp: 0, sensor: String::from("cpu0"), metric: SensorMetric::Temperature, value: 56.20 },
        Event { timestamp: 0, sensor: String::from("cpu1"), metric: SensorMetric::Temperature, value: 33.33 },
        Event { timestamp: 0, sensor: String::from("gpu0"), metric: SensorMetric::Temperature, value: 25.00 },
    ];

    for aggr in &all {
        for (key, val) in aggr.aggregate(events) {
            println!("{} {:?}: {:.02}", aggr.name(), key, val);
        }
    }
    // total "Temperature": 38.18
    // total "Load": 4.82
    // total "Frequency": 2166.67
    // Load "gpu0": 13.45
    // Load "cpu1": 0.04
    // Load "cpu0": 0.98
    // Temperature "cpu1": 33.33
    // Temperature "cpu0": 56.20
    // Temperature "gpu0": 25.00
}