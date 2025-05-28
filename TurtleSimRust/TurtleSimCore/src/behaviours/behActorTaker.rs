pub trait ActorTakerBehaviour {
    fn CanTakeActor(&self, actor: i64) -> bool {
        false
    }

    fn TakeActor(&mut self, actor: i64) -> bool {
        false
    }
}
