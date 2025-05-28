pub trait Entity {
    fn update(&self);
    fn get_name(&self) -> &String;
    fn step();
}
//
// pub fn cast_entity_to<T: 'static>(entity: &dyn Entity) -> Option<&T>
// where
//     T: Any,
// {
//     // Attempt to cast the trait object to the specific type
//     entity.as_any().downcast_ref::<T>()
// }
