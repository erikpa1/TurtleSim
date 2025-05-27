pub trait BehaviourActorTaker {
    fn CanTakeActor(&self, actor: std::any) -> bool {
        false
    }

    fn TakeActor(&mut self, actor: std::any) -> bool {
        false
    }
}
